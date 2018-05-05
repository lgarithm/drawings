#pragma once


#include <rey/base/config.h>
#include <rey/linear/tuple.h>

#define DEFINE_DET_2X2(T)                                                      \
    T det(T A, T B, T C, T D) { return A * D - B * C; }

#define DEFINE_CROSS_PROD(T, X, Y, Z)                                          \
    T cross(const T &p, const T &q)                                            \
    {                                                                          \
        return T{det(p.Y, p.Z, q.Y, q.Z), det(p.Z, p.X, q.Z, q.X),             \
                 det(p.X, p.Y, q.X, q.Y)};                                     \
    }

typedef SCALAR_T scalarT;

DEFINE_TUPLE_2(vector2, scalarT, x, y);
DEFINE_TUPLE_3(vector3, scalarT, x, y, z);
DEFINE_TUPLE_4(vector4, scalarT, x, y, z, w);

DECLARE_TUPLE_2_SUB(vector2, x, y);
DECLARE_TUPLE_2_DET(scalarT, vector2, x, y);

DECLARE_TUPLE_3_NEG(vector3, x, y, z);
DECLARE_TUPLE_3_EQU(vector3, x, y, z);
DECLARE_TUPLE_3_INC(vector3, x, y, z);
DECLARE_TUPLE_3_ADD(vector3, x, y, z);
DECLARE_TUPLE_3_SUB(vector3, x, y, z);
DECLARE_TUPLE_3_DIV(vector3, x, y, z);
DECLARE_TUPLE_3_DOT(scalarT, vector3, x, y, z);
DECLARE_TUPLE_3_SCALE(scalarT, vector3, x, y, z);

DEFINE_TUPLE_2(point2, scalarT, x, y);
DEFINE_TUPLE_3(point3, scalarT, x, y, z);
DEFINE_TUPLE_4(point4, scalarT, x, y, z, w);

DECLARE_TUPLE_2_DIS(point2, vector2, x, y);

DECLARE_TUPLE_3_EQU(point3, x, y, z);
DECLARE_TUPLE_3_DIV(point3, x, y, z);
DECLARE_TUPLE_3_DIS(point3, vector3, x, y, z);

DECLARE_TUPLE_3_SCALE(scalarT, point3, x, y, z);

DECLARE_TUPLE_3_MOV(point3, vector3, x, y, z);
DECLARE_TUPLE_3_L_1_1(scalarT, point3, vector3, x, y, z);

DEFINE_TUPLE_3(simplex2, point3, a, b, c);
DEFINE_TUPLE_4(matrix4, vector4, o, p, q, r);

vector3 cross(const vector3 &, const vector3 &);
vector3 reflect(const vector3 &, const vector3 &);

scalarT det(const matrix4 &);
scalarT vol6(const point3 &, const point3 &, const point3 &, const point3 &);
scalarT area2(const point3 &, const point3 &, const point3 &);
scalarT dis(const point3 &, const simplex2 &);
bool in(const point3 &, const simplex2 &s);


