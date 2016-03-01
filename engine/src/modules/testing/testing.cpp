#include "testing.h"

#include <cstdio>

#include "logger.h"

void assert_eq(double x, double y)
{
  double e = fabs(x - y);
  char msg[64];
  sprintf(msg, "asserting %f == %f, delta=%f", x, y, e);
  clogger lo;
  lo.log(msg);
  assert(e < 1e-6);
}
