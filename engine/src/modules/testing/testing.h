#ifndef TESTING_H
#define TESTING_H

#include <cassert>
#include <cmath>

#include "logger.h"

template<typename T>void assert_eq(T x, T y) { assert(x == y); }

void assert_eq(double x, double y);

#define test(x)                                 \
  {                                             \
    slogger _("test_"#x);                       \
    test_##x();                                 \
  }

#endif  // TESTING_H
