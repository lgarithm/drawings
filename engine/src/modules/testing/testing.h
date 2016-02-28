#ifndef TESTING_H
#define TESTING_H

#include <cassert>
#include <cmath>
#include <cstdio>

#include "logger.h"

template<typename T>void assert_eq(T x, T y) { assert(x == y); }

void assert_eq(double x, double y)
{
  double e = fabs(x - y);
  char msg[64];
  sprintf(msg, "asserting %f == %f, delta=%f", x, y, e);
  clogger lo;
  lo.log(msg);
  assert(e < 1e-6);
}

#define test(x) \
  { \
    slogger _("test_"#x); \
    test_##x(); \
  }

#endif  // TESTING_H
