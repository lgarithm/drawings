#ifndef POINT_H
#define POINT_H

#ifdef USE_TEMPLATE

#include "point_impl_tpl.h"

#else

#include "point_impl_macro.h"

bool operator==(const point3&, const point3&);
point3 operator*(pointT, const point3&);
point3 operator+(const point3&, const point3&);
point3 operator-(const point3&, const point3&);
point3 cross(const point3&, const point3&);
pointT dot(const point3&, const point3&);
point3 reflect(const point3&, const point3&);
#endif

vector3 vec3(pointT x, pointT y, pointT z);
pointT len(const vector3& p);
vector3 norm(const vector3& p);

#endif  // POINT_H
