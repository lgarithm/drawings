#include "primitives.h"

#include <cmath>

#include "guard.h"
#include "maybe.h"
#include "model.h"
#include "point.h"

Plane::Plane(const t_vector& n) : n(n) { assert_unit(n.v, __func__); }

maybe<point3> Plane::intersect(const ray& r) const
{
  assert_unit(r.v, __func__);
  auto c = dot(n.v, r.v);
  if (c < 0) {
    auto l = dot(n.v, n.o - r.o);
    if (l < 0) {
      auto t = l / c;
      return just<point3>(r + t);
    }
  }
  return nothing<point3>();
}

surface Plane::at(const point3&) const
{
  auto s = surface{n};
  return s;
}

maybe<point3> Floor::intersect(const ray& r) const
{
  if (r.v.z != 0) {
    auto d = - r.o.z / r.v.z;
    if (d > 0) {
      return just<point3>(r + d);
    }
  }
  return nothing<point3>();
}

surface Floor::at(const point3& p) const
{
  auto s = surface{t_vector{p, z_axis}};
  s.m.diffuse = .4 * grey;
  return s;
}

Chessboard::Chessboard(double gs) : grid_size(gs) {}

surface Chessboard::at(const point3& p) const
{
  auto s = surface{t_vector{p, z_axis}};
  int xx = int(floor(p.x / grid_size)) & 1;
  int yy = int(floor(p.y / grid_size)) & 1;
  if (xx == yy) {
    s.m.diffuse = white;
  } else {
    s.m.diffuse = black;
  }
  return s;
}

sphere::sphere(double size, const point3& pos): size(size), pos(pos) {}

maybe<point3> sphere::intersect(const ray& r) const
{
  auto ro = pos - r.o;
  auto v = dot(ro, r.v);
  if (v >= 0) {
    auto disc = size * size + v * v - dot(ro, ro);
    if (disc >= 0) {
      return just<point3>(r + (v - sqrt(disc)));
    }
  }
  return nothing<point3>();
}

surface sphere::at(const point3& p) const
{
  auto s = surface{t_vector{p, norm(p - pos)}};
  return s;
}

triangle::triangle(const point3& a, const point3& b, const point3& c)
  : a(a), b(b), c(c) {}

maybe<point3> triangle::intersect(const ray& r) const
{
  auto n = norm(a, b, c);
  auto th = -dot(r.v, n);
  if (th > 0) {
    auto d = dis(r.o, simplex2{a, b, c});
    if (d > 0) {
      auto t = d / th;
      auto e = r + t;
      if (in(e, simplex2{a,b,c})) {
        return just<point3>(e);
      }
    }
  }
  return nothing<point3>();
}

surface triangle::at(const point3& p) const
{
  auto s = surface{t_vector{p, norm(a,b,c)}};
  s.m.reflection = 1;
  s.m.specular = white;
  s.m.roughness = 1;
  return s;
}
