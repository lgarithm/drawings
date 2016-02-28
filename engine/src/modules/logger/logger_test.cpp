#include "logger.h"

#include <cstdio>

void test_1()
{
  clogger lo;
  for (int j=0; j < 2; ++j) {
    for (int i=30; i < 48; ++i) {
      char msg[64];
      sprintf(msg, "[%d;%d", j, i);
      lo.log(msg, i, j);
    }
  }
}

int main()
{
  test_1();
  return 0;
}
