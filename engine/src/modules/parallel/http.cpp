#include "http.h"

#include <cstdio>
#include <cstring>

#include <string>

#include <unistd.h>

using std::string;


http_request* parse_http_request(char* buffer, int n)
{
  auto req = new http_request;
  buffer[n] = '\0';
  req->request_line = buffer;
  req->path = buffer + 4;
  {
    char * p = req->path;
    for (; *p != ' ' && *p != '\0'; ++p);
    req->path_len = p - req->path;
  }
  {
    char * p = req->path + req->path_len;
    for (; *p != '\r' && *p != '\0'; ++p);
    req->headers = p + 2;
    req->headers_len = n - (req->headers - buffer);
  }
  return req;
}

void _server_usage(const char * hostname, int port,
                   char * server_usage,
                   char * server_usage_html)
{
  static const char format[] = ("Usage:\r\n"
                                "GET /render HTTP/1.1\r\n"
                                "X-Rey: args\r\n"
                                "\r\n"
                                "curl \\\r\n"
                                "\t-H \"X-Rey: -m\" \\\r\n"
                                "\t-H \"X-Rey: sphere(1, (0,0,1))\" \\\r\n"
                                "\t%s:%d/render\r\n"
                                "\r\n");
  sprintf(server_usage, format, hostname, port);
  static const char html_format[] =
    ("<!doctype html><html><head><title>Render Server</title></head>"
     "<body><a target=\"_blank\" href=\"/render\">render</a>"
     "</body></html>");
  sprintf(server_usage_html, html_format);
}


render_request::render_request() : args({"render"}),
                 test(false),
                 http_header(true),
                 bmp_header(true),
                 bmp_padding(true) { }

render_request parse_http_headers(char * buffer, int n)
{
  const char * end = buffer + n;
  render_request rr;
  for (char * p = buffer; p < end; ) {
    char * q = p;
    for (; *q != '\r' && q < end; ++q);
    *q = '\0';
    if (q - p > 7 && strncmp("X-Rey: ", p, 7) == 0) {
      auto arg = string(p + 7, q);
      if (arg == "test") {
        rr.test = true;
      } else if (arg == "no-http-header") {
        rr.http_header = false;
      } else if (arg == "no-bmp-header") {
        rr.bmp_header = false;
      } else if (arg == "no-bmp-padding") {
        rr.bmp_padding = false;
      } else {
        rr.args.push_back(arg);
      }
    }
    p = q + 2;
  }
  return rr;
}

#define UNCHECK(expr) ({auto _ = expr;})

void send_static_body(int fd, const char * header_format, const char * body)
{
  char head[1024];
  int len = strlen(body);
  sprintf(head, header_format, len);
  UNCHECK(write(fd, head, strlen(head)));
  UNCHECK(write(fd, body, len));
}

void send_text_body(int fd, const char * body)
{ send_static_body(fd, text_header_format, body); }

void send_html_body(int fd, const char * body)
{ send_static_body(fd, html_header_format, body); }

void send_raw_body(int fd, const char * body)
{ UNCHECK(write(fd, body, strlen(body))); }
