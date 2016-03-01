#ifndef POINT_H
#define POINT_H

#ifdef USE_TEMPLATE

#include "point_impl_tpl.h"

#else

#include "point_impl_macro.h"

bool operator==(const point3&, const point3&);
point3 operator*(scalarT, const point3&);
point3 operator+(const point3&, const point3&);
point3 operator-(const point3&, const point3&);
point3 cross(const point3&, const point3&);
scalarT dot(const point3&, const point3&);
point3 reflect(const point3&, const point3&);
scalarT det(const matrix4&);
scalarT vol6(const point3&, const point3&, const point3&, const point3&);
scalarT area2(const point3&, const point3&, const point3&);
scalarT dis(const point3&, const simplex2&);
bool in(const point3&, const simplex2& s);
#endif  // USE_TEMPLATE

vector3 vec3(scalarT, scalarT, scalarT);
vector4 vec4(scalarT, scalarT, scalarT, scalarT);
matrix4 mat4(const vector3&, const vector3&, const vector3&, const vector3&);
matrix4 mat4(const vector4&, const vector4&, const vector4&, const vector4&);
scalarT len(const vector3&);
vector3 norm(const vector3&);
vector3 norm(const vector3&, const vector3&, const vector3&);

static const auto origin = point3{0,0,0};
static const auto x_axis = vec3(1,0,0);
static const auto y_axis = vec3(0,1,0);
static const auto z_axis = vec3(0,0,1);

#endif  // POINT_H
