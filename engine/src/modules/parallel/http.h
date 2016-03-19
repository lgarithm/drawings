#ifndef HTTP_H
#define HTTP_H

#include <string>
#include <vector>

static const char status_204[] = ("HTTP/1.1 204 OK\r\n"
                                  "Content-Type: text/plain\r\n"
                                  "Content-Length: 0\r\n"
                                  "\r\n");

static const char status_400[] = ("HTTP/1.1 400 Bad Request\r\n"
                                  "\r\n");

static const char status_404[] = ("HTTP/1.1 404 Not Found\r\n"
                                  "Content-Type: text/plain\r\n"
                                  "Content-Length: 0\r\n"
                                  "\r\n");

#define STATUS_200 "HTTP/1.1 200 OK\r\n"

static const char text_header_format[] = (STATUS_200
                                          "Content-Length: %d\r\n"
                                          "Content-Type: text/plain\r\n"
                                          "\r\n");

static const char html_header_format[] = (STATUS_200
                                          "Content-Length: %d\r\n"
                                          "Content-Type: text/html\r\n"
                                          "\r\n");

static const char byte_header_format[] = (STATUS_200
                                          "Content-Length: %d\r\n"
                                          "Content-Type:"
                                          " application/octet-stream\r\n"
                                          "Content-Transfer-Encoding: 8BIT\r\n"
                                          "Content-Disposition: attachment;"
                                          " filename=\"output.bmp\"\r\n"
                                          "\r\n");

void _server_usage(const char *, int, char *, char *);

struct http_request
{
  char * request_line;
  char * path;
  int path_len;
  char * headers;
  int headers_len;
};

http_request* parse_http_request(char*, int);

struct render_request
{
  std::vector<std::string> args;
  bool test;
  bool http_header;
  bool bmp_header;
  bool bmp_padding;

  render_request();
};

render_request parse_http_headers(char *, int);

void send_text_body(int, const char *);
void send_html_body(int, const char *);

#endif
