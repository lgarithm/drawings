#include "arith.h"

#include <cmath>

#include "tuple.h"

DEFINE_TUPLE_2_SCALE(numericT, linear_eq, A, B);
DEFINE_TUPLE_2_PLUS(linear_eq, A, B);

quad_eq operator*(const linear_eq& l, const linear_eq& r)
{ return quad_eq{l.A * r.A, l.A * r.B + l.B * r.A, l.B * r.B}; }

quad_eq sqr(const linear_eq& leq) { return leq * leq; }

DEFINE_TUPLE_3_SCALE(numericT, quad_eq, A, B, C);
DEFINE_TUPLE_3_PLUS(quad_eq, A, B, C);

unsigned short real_roots(const quad_eq& e, numericT& x1, numericT& x2)
{
  auto delta = e.B * e.B - 4 * e.A * e.C;
  if (delta < 0) return 0;
  auto a2 = e.A + e.A;
  if (delta == 0) {
    x1 = x2 = -e.B / a2;
    return 1;
  } else {
    auto d = sqrt(delta);
    x1 = (-e.B - d) / a2;
    x2 = (-e.B + d) / a2;
    return 2;
  }
}

unsigned short positive_roots(const quad_eq& e, numericT& x1, numericT& x2)
{
  auto n = real_roots(e, x1, x2);
  if (n == 0) return 0;
  if (n == 1) return x1 > 0 ? 1 : 0;
  if (x1 > 0) return 2;
  if (x2 > 0) {
    x1 = x2;
    return 1;
  }
  return 0;
}
