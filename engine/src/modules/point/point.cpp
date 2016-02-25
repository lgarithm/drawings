#include "point.h"

#include <cmath>

#ifdef USE_TEMPLATE

point3 vec3(pointT x, pointT y, pointT z) { return point3_t<pointT>{x, y, z}; }

#else

point3 vec3(pointT x, pointT y, pointT z) { return point3{x, y, z}; }

DEFINE_DET_2X2(pointT);
DEFINE_TUPLE3_EQUAL(point3, x, y, z);
DEFINE_TUPLE_3_SCALE(pointT, point3, x, y, z);
DEFINE_TUPLE_3_PLUS(point3, x, y, z);
DEFINE_TUPLE_3_MINUS(point3, x, y, z);
DEFINE_DOT_3(pointT, point3, x, y, z);
DEFINE_CROSS_PROD(point3, x, y, z);
DEFINE_REFLECT_3(pointT, point3);
#endif


pointT len(const point3& p) { return sqrt(dot(p, p)); }

point3 norm(const point3& p)
{
  pointT l = len(p);
  return l == 0 ? p : (1.0 / l) * p;
}
