#ifndef POINT_IMPL_MACRO_H
#define POINT_IMPL_MACRO_H

#include "tuple.h"

#define DEFINE_DET_2X2(T) T det(T A, T B, T C, T D) {return A * D - B * C; }

#define DEFINE_DOT_3(T, P, X, Y, Z) \
  T dot(const P& p, const P& q) \
  { return p.X * q.X + p.Y * q.Y + p.Z * q.Z; }

#define DEFINE_CROSS_PROD(T, X, Y, Z) \
  T cross(const T& p, const T& q) \
  { return T{det(p.Y, p.Z, q.Y, q.Z), \
	     det(p.Z, p.X, q.Z, q.X), \
             det(p.X, p.Y, q.X, q.Y)}; }

#define DEFINE_REFLECT_3(T, P) \
  P reflect(const P& n, const P& d) \
  { return d - T(2) * dot(n, d) * n; }

typedef double pointT;
DEFINE_TUPLE_2(point2, pointT, x, y);
DEFINE_TUPLE_3(point3, pointT, x, y, z);
typedef point3 vector3;

#endif  // POINT_IMPL_MACRO_H
