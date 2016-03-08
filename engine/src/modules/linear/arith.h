#ifndef ARITH_H
#define ARITH_H

#include <cmath>

#include "config.h"
#include "tuple.h"

typedef SCALAR_T numericT;

template<typename T> bool zero(T x) { return fabs(x) < 1e-12; }

DEFINE_TUPLE_2(linear_eq, numericT, A, B);
DEFINE_TUPLE_3(quad_eq, numericT, A, B, C);

linear_eq operator*(numericT, const linear_eq&);
quad_eq operator*(const linear_eq&, const linear_eq&);
quad_eq sqr(const linear_eq&);
quad_eq operator+(const quad_eq&, const quad_eq&);
unsigned short real_roots(const quad_eq&, numericT&, numericT&);
unsigned short positive_roots(const quad_eq&, numericT&, numericT&);

#endif  // ARITH_H
