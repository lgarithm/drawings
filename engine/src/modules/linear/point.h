#ifndef POINT_H
#define POINT_H

#ifdef USE_TEMPLATE

#include "point_impl_tpl.h"

#else

#include "point_impl_macro.h"

#endif // USE_TEMPLATE

vector3 vec3(scalarT, scalarT, scalarT);
vector4 vec4(scalarT, scalarT, scalarT, scalarT);

point2 pos2(scalarT, scalarT);
point3 pos3(scalarT, scalarT, scalarT);

matrix4 mat4(const vector3 &, const vector3 &, const vector3 &,
             const vector3 &);
matrix4 mat4(const vector4 &, const vector4 &, const vector4 &,
             const vector4 &);
scalarT len(const vector3 &);
vector3 norm(const vector3 &);
vector3 norm(const vector3 &, const vector3 &, const vector3 &);

static const auto origin = pos3(0, 0, 0);
static const auto x_axis = vec3(1, 0, 0);
static const auto y_axis = vec3(0, 1, 0);
static const auto z_axis = vec3(0, 0, 1);

#endif // POINT_H
