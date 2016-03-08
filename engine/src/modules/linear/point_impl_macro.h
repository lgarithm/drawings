#ifndef POINT_IMPL_MACRO_H
#define POINT_IMPL_MACRO_H

#include "config.h"
#include "tuple.h"

#define DEFINE_DET_2X2(T) T det(T A, T B, T C, T D) { return A * D - B * C; }

#define DEFINE_CROSS_PROD(T, X, Y, Z)           \
  T cross(const T& p, const T& q)               \
  { return T{det(p.Y, p.Z, q.Y, q.Z),           \
        det(p.Z, p.X, q.Z, q.X),                \
        det(p.X, p.Y, q.X, q.Y)}; }

typedef SCALAR_T scalarT;
DEFINE_TUPLE_2(point2, scalarT, x, y);
DEFINE_TUPLE_3(point3, scalarT, x, y, z);
DEFINE_TUPLE_4(point4, scalarT, x, y, z, w);
typedef point2 vector2;
typedef point3 vector3;
typedef point4 vector4;
DEFINE_TUPLE_3(simplex2, point3, a, b, c);
DEFINE_TUPLE_4(matrix4, vector4, o, p, q, r);

scalarT det(const point2&, const point2&);
point2 operator-(const point2&, const point2&);

point3 operator-(const point3&);
bool operator==(const point3&, const point3&);
point3 operator*(scalarT, const point3&);
void operator+=(point3&, const point3&);
point3 operator+(const point3&, const point3&);
point3 operator-(const point3&, const point3&);
point3 operator/(const point3&, const point3&);
point3 cross(const point3&, const point3&);
scalarT dot(const point3&, const point3&);
vector3 reflect(const vector3&, const vector3&);

scalarT det(const matrix4&);
scalarT vol6(const point3&, const point3&, const point3&, const point3&);
scalarT area2(const point3&, const point3&, const point3&);
scalarT dis(const point3&, const simplex2&);
bool in(const point3&, const simplex2& s);

#endif  // POINT_IMPL_MACRO_H
