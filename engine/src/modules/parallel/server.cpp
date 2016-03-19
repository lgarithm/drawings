#include "server.h"

#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <atomic>
#include <memory>
#include <string>
#include <thread>
#include <vector>

#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "app.h"
#include "bmp.h"
#include "debug.h"
#include "http.h"
#include "model.h"
#include "params.h"

using std::atomic;
using std::string;
using std::thread;
using std::unique_ptr;
using std::vector;

namespace {
  const auto max_conn = 10;
  atomic<int> living_tasks(0);
  atomic<int> request_id(0);

  static const int buffer_size = 3 * max_width * max_height;
  unsigned char s_buffers[max_conn][buffer_size];
  static char server_usage[1024];
  static char server_usage_html[1024];
}  // namespace

struct render_handler
{
  const int fd;
  const render_request rr;
  render_handler(int fd, const render_request& rr) : fd(fd), rr(rr) { }

  void operator()()
  {
    config cfg;
    int argc = rr.args.size();
    const char * argv[argc];
    for (int i=0; i < argc; ++i) argv[i] = rr.args[i].c_str();
    if (not parse(argc, argv, cfg)) {
      write(fd, status_400, sizeof(status_400));
      return ;
    }
    if (rr.http_header) {
      char head[1024];
      bmp_head bh;
      bh.init(cfg.d.width, cfg.d.height);
      sprintf(head, byte_header_format, bh.header.file_size);
      write(fd, head, strlen(head));
    }
    int idx = (request_id++) % max_conn;
    printf("using buffer %d\n", idx);
    cfg.buffer = s_buffers[idx];
    cfg.outfd = fd;
    cfg.bmp_padding = rr.bmp_padding;
    usleep(50 * 1000);
    run(cfg);
    usleep(50 * 1000);
  }
};

struct connection
{
  const int idx;
  const int fd;

  connection(int idx, int fd) : idx(idx), fd(fd) { living_tasks++; }

  ~connection()
  {
    if (-1 == shutdown(fd, SHUT_RDWR)) {
      perror("shutdown failed");
    }
    close(fd);
    living_tasks--;
    printf("fd %d done, living_tasks: %d\n", fd, living_tasks.load());
  }

  void operator()()
  {
    if (living_tasks >= max_conn) {
      write(fd, status_204, sizeof(status_204));
      return ;
    }
    const auto buffer_size = (1 << 10) - 1;
    char input[buffer_size + 1];
    auto n = read(fd, input, buffer_size);
    unique_ptr<http_request> req(parse_http_request(input, n));
    auto path = string(req->path, req->path_len);

    if (path == "/render") {
      auto rr = parse_http_headers(req->headers, req->headers_len);
      if (rr.test) {
        char body[1024];
        {
          char * p = body;
          for (auto it : rr.args) {
            sprintf(p, "\t%s\n", it.c_str());
            p += strlen(p);
          }
        }
        send_text_body(fd, body);
      } else {
        render_handler(fd, rr)();
      }
    } else if (path == "/") {
      send_text_body(fd, server_usage);
    } else if (path == "/index") {
      send_html_body(fd, server_usage_html);
    } else {
      write(fd, status_404, sizeof(status_404));
    }
  }
};

server::server(int port, const string& hostname)
  : port(port), hostname(hostname), fd(-1), fast_fail(true)
{
  _server_usage(hostname.c_str(), port, server_usage, server_usage_html);

  fd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
  if (-1 == fd) {
    perror("cannot create socket");
    exit(EXIT_FAILURE);
  }

  sockaddr_in sa;
  memset(&sa, 0, sizeof sa);
  sa.sin_family = AF_INET;
  sa.sin_port = htons(port);
  sa.sin_addr.s_addr = htonl(INADDR_ANY);
  if (-1 == bind(fd, (sockaddr *) &sa, sizeof(sa))) {
    perror("bind failed");
    close(fd);
    exit(EXIT_FAILURE);
  }
  if (-1 == listen(fd, 10)) {
    perror("listen failed");
    close(fd);
    exit(EXIT_FAILURE);
  }
}

server::~server()
{
  if (fd > 0) {
    printf("shutting down\n");
    close(fd);
    printf(".\n");
  }
}

void server::operator()()
{
  for (int idx=1; ;) {
    if (living_tasks < max_conn) {
      int conn = accept(fd, nullptr, nullptr);
      printf("%d-th connection accepted\n", idx);
      if (conn < 0) {
        perror("accept failed");
        if (fast_fail) {
          close(fd);
          exit(EXIT_FAILURE);
        } else {
          printf("continue\n");
          continue;
        }
      }
      auto th = new thread(wrap(new connection(idx++, conn)));
    } else {
      printf("thread full\n");
      usleep(100 * 1000);
    }
  }
}
