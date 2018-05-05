#pragma once

#include <cmath>

#include <rey/base/config.h>
#include <rey/linear/tuple.h>

using numericT = SCALAR_T;

template <typename T> bool zero(T x) { return fabs(x) < 1e-12; }

DEFINE_TUPLE_2(linear_eq, numericT, A, B);
DEFINE_TUPLE_3(quad_eq, numericT, A, B, C);

DECLARE_TUPLE_2_SCALE(numericT, linear_eq, A, B);
DECLARE_TUPLE_3_SCALE(numericT, quad_eq, A, B, C);
DECLARE_TUPLE_3_ADD(quad_eq, A, B, C);
DECLARE_TUPLE_3_SUB(quad_eq, A, B, C);

numericT eval(const linear_eq &, numericT);
numericT eval(const quad_eq &, numericT);

quad_eq operator*(const linear_eq &, const linear_eq &);
quad_eq sqr(const linear_eq &);
unsigned short real_roots(const quad_eq &, numericT &, numericT &);
unsigned short positive_roots(const quad_eq &, numericT &, numericT &);
bool min_positive_root(const quad_eq &e, numericT &x);

static auto const radian = 180 / M_PI;
