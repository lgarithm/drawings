#include "primitives.h"

#include <cmath>

#include "affine.h"
#include "guard.h"
#include "maybe.h"
#include "model.h"
#include "point.h"


plane::plane(const t_vector3& n) : n(n) { assert_unit(n.v, __func__); }

maybe<scalarT> plane::meet(const ray& r) const { return r_dis(n, r); }

vector3 plane::at(const point3&) const { return n.v; }


Floor::Floor() : plane(t_vector3(origin, z_axis)) { m.diffuse = .4 * grey; }


disc::disc(scalarT r, const t_vector3& n) : bound(plane(n)), R(r) { }

bool disc::in(const point3& p) const { return len(p - n.o) < R; }

point3 gc(const point3& a, const point3& b, const point3& c)
{ return origin + (1 / 3.0) * (a + (b - origin) + (c - origin) - origin); }

triangle::triangle(const point3& a, const point3& b, const point3& c)
  : bound(plane(t_vector3{gc(a, b, c),
          norm(a - origin, b - origin, c - origin)}))
  , a(a), b(b), c(c) { }

bool triangle::in(const point3& p) const { return ::in(p, simplex2{a,b,c}); }

quad::quad(const oframe& of, scalarT w, scalarT h)
  : bound(plane(t_vector3(of.o, of.f.Z)))
  , of(of), half_w(.5 * w), half_h(.5 * h) { }

bool quad::in(const point3& p) const
{
  auto q = local(of, p);
  return fabs(q.x) < half_w and fabs(q.y) < half_h;
}


Chessboard::Chessboard(double gs) :
  grid_size(gs), plane(t_vector3(origin, z_axis)) { }

material Chessboard::mt(const point3& p) const
{
  material m;
  int xx = int(floor(p.x / grid_size)) & 1;
  int yy = int(floor(p.y / grid_size)) & 1;
  if (xx == yy) {
    m.diffuse = white;
  } else {
    m.diffuse = black;
  }
  return m;
}

sphere::sphere(double size, const point3& pos): size(size), pos(pos) { }

maybe<scalarT> sphere::meet(const ray& r) const
{
  auto ro = pos - r.o;
  auto v = dot(ro, r.v);
  if (v >= 0) {
    auto disc = size * size + v * v - dot(ro, ro);
    if (disc >= 0) {
      return just<scalarT>(v - sqrt(disc));
    }
  }
  return nothing<scalarT>();
}

vector3 sphere::at(const point3& p) const { return norm(p - pos); }


tetrahedron::tetrahedron(const point3& a, const point3& b, const point3& c,
                         const point3& d)
  : f{triangle(a,b,c), triangle(c,b,d), triangle(b,a,d), triangle(a,c,d)}
  , subs{f, f + 1, f + 2, f + 3} { }

maybe<intersection> tetrahedron::intersect(const ray& r) const
{ return nearest(subs, r); }


maybe<scalarT> r_dis(const t_vector3& n, const ray& r)
{
  assert_unit(r.v, __func__);
  auto c = dot(n.v, r.v);
  if (c < 0) {
    auto l = dot(n.v, n.o - r.o);
    if (l < 0) return just<scalarT>(l / c);
  }
  return nothing<scalarT>();
}
