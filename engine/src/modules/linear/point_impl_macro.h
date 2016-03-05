#ifndef POINT_IMPL_MACRO_H
#define POINT_IMPL_MACRO_H

#include "config.h"
#include "tuple.h"

#define DEFINE_DET_2X2(T) T det(T A, T B, T C, T D) { return A * D - B * C; }

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

typedef SCALAR_T scalarT;
DEFINE_TUPLE_2(point2, scalarT, x, y);
DEFINE_TUPLE_3(point3, scalarT, x, y, z);
DEFINE_TUPLE_4(point4, scalarT, x, y, z, w);
typedef point3 vector3;
typedef point4 vector4;
DEFINE_TUPLE_3(simplex2, point3, a, b, c);
DEFINE_TUPLE_4(matrix4, vector4, o, p, q, r);
#endif  // POINT_IMPL_MACRO_H
