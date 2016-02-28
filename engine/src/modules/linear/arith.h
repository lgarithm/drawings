#ifndef ARITH_H
#define ARITH_H

#include <cmath>

template<typename T> bool zero(T x) { return fabs(x) < 1e-12; }

#endif  // ARITH_H
