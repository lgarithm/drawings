#include "point.h"

#include <cassert>
#include <cmath>
#include <cstring>

#include <algorithm>

#include "arith.h"

using std::next_permutation;

#ifdef USE_TEMPLATE

point3 vec3(scalarT x, scalarT y, scalarT z)
{ return point3_t<scalarT>{x, y, z}; }

#else

vector3 vec3(scalarT x, scalarT y, scalarT z) { return point3{x, y, z}; }

vector4 vec4(scalarT x, scalarT y, scalarT z, scalarT w)
{ return point4{x, y, z, w}; }

vector4 vec4(const vector3& v, scalarT w) { return vec4(v.x, v.y, v.z, w); }

matrix4 mat4(const vector4& o, const vector4& p, const vector4& q,
             const vector4& r) { return matrix4{o, p, q, r}; }

matrix4 mat4(const vector3& o, const vector3& p, const vector3& q,
             const vector3& r)
{ return matrix4{vec4(o, 1), vec4(p, 1), vec4(q, 1), vec4(r, 1)}; }

DEFINE_DET_2X2(scalarT);
DEFINE_TUPLE_2_DET(scalarT, point2, x, y);
DEFINE_TUPLE_2_MINUS(point2, x, y);

DEFINE_TUPLE_3_NEGATIVE(point3, x, y, z);
DEFINE_TUPLE_3_EQUAL(point3, x, y, z);
DEFINE_TUPLE_3_INC(point3, x, y, z);
DEFINE_TUPLE_3_SCALE(scalarT, point3, x, y, z);
DEFINE_TUPLE_3_PLUS(point3, x, y, z);
DEFINE_TUPLE_3_MINUS(point3, x, y, z);
DEFINE_TUPLE_3_DIV(point3, x, y, z);

DEFINE_TUPLE_3_DOT(scalarT, point3, x, y, z);
DEFINE_CROSS_PROD(point3, x, y, z);

vector3 reflect(const vector3& n, const vector3& d)
{ return d - 2 * dot(n, d) * n; }

#endif

scalarT len(const vector3& p) { return sqrt(dot(p, p)); }

vector3 norm(const vector3& p)
{
  scalarT l = len(p);
  assert(l != 0);
  return l == 0 ? p : (1.0 / l) * p;
}

vector3 norm(const vector3& a, const vector3& b, const vector3& c)
{ return norm(cross(b - a, c - a)); }

scalarT det(const matrix4& m)
{
  scalarT mm[4][4];
  memcpy(mm, &m, sizeof(scalarT) * 16);

  scalarT d = 0;
  int idx[] = {0,1,2,3};
  do {
    int s = 0;
    for (int i=0; i < 4; ++i)
      for (int j=0; j < i; ++j)
        if (idx[i] < idx[j]) ++s;

    scalarT p = s & 1 ? -1 : 1;
    for (int i=0; i < 4; ++i) p *= mm[i][idx[i]];
    d += p;
  } while (next_permutation(idx, idx + 4));
  return d;
}

scalarT vol6(const point3& a, const point3& b, const point3& c, const point3& d)
{ return -det(mat4(a,b,c,d)); }

scalarT area2(const point3& a, const point3& b, const point3& c)
{ return len(cross(b - a, b - c)); }

scalarT dis(const point3& o, const simplex2& s)
{ return vol6(s.a, s.b, s.c, o) / area2(s.a, s.b, s.c); }

bool in(const point3&o, const simplex2& s)
{
  return zero(area2(s.a, s.b, s.c) -
              area2(o, s.a, s.b) -
              area2(o, s.b, s.c) -
              area2(o, s.c, s.a));

}
