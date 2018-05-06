#pragma once
#include <cmath>

#include <rey/base/config.h>
#include <rey/linear/linear.hpp>

using numericT = SCALAR_T;

struct LinearEquation;
struct QuadraticEquation;

using linear_eq = rey::linear::tuple::_tuple_t<numericT, 2, LinearEquation>;
using quad_eq = rey::linear::tuple::_tuple_t<numericT, 3, QuadraticEquation>;

numericT eval(const linear_eq &, numericT);
numericT eval(const quad_eq &, numericT);

extern quad_eq operator*(const linear_eq &, const linear_eq &);
extern quad_eq operator+(const quad_eq &, const quad_eq &);
extern quad_eq operator-(const quad_eq &, const quad_eq &);
extern quad_eq sqr(const linear_eq &);

extern unsigned short real_roots(const quad_eq &, numericT &, numericT &);
extern unsigned short positive_roots(const quad_eq &, numericT &, numericT &);
extern bool min_positive_root(const quad_eq &e, numericT &x);

static auto const radian = 180 / M_PI;
