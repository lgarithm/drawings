#include "primitives.h"

#include <cmath>

#include "maybe.h"
#include "model.h"
#include "point.h"


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

plane_alg_impl::plane_alg_impl(const vector3& n, scalarT d) : n(n), d(d) { }

maybe<scalarT> plane_alg_impl::meet(const ray& r) const
{
  auto u = dot(n, r.v);
  if (u != 0) {
    auto t = (dot(r.o, n) + d) / u;
    if (t > 0) {
      return just(t);
    }
  }
  return nothing<scalarT>();
}

t_vector3 plane_alg_impl::at(const point3& p) const { return t_vector3{p, n}; }


plane::plane(const t_vector3& n) : n(n) { assert_unit(n.v, __func__); }

maybe<scalarT> plane::meet(const ray& r) const { return r_dis(n, r); }

t_vector3 plane::at(const point3& p) const { return t_vector3{p, n.v}; }


disc::disc(scalarT r, const t_vector3& n) : plane(n), R(r) { }

maybe<scalarT> disc::meet(const ray& r) const
{
  auto t = plane::meet(r);
  if (t.just) {
    auto d = len(r + t.it - n.o);
    if (d < R) return t;
  }
  return nothing<scalarT>();
}


maybe<scalarT> f_dis(const ray& r)
{
  if (r.v.z != 0) {
    auto d = - r.o.z / r.v.z;
    if (d > 0) return just<scalarT>(d);
  }
  return nothing<scalarT>();
}

Floor::Floor() { m.diffuse = .4 * grey; }

maybe<scalarT> Floor::meet(const ray& r) const { return f_dis(r); }

t_vector3 Floor::at(const point3& p) const { return t_vector3{p, z_axis}; }

Chessboard::Chessboard(double gs) : grid_size(gs) {}

maybe<scalarT> Chessboard::meet(const ray& r) const { return f_dis(r); }

t_vector3 Chessboard::at(const point3& p) const { return t_vector3{p, z_axis}; }

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

t_vector3 sphere::at(const point3& p) const
{ return t_vector3{p, norm(p - pos)}; }

triangle::triangle(const point3& a, const point3& b, const point3& c)
  : a(a), b(b), c(c)
{
  m.reflection = 1;
  m.specular = white;
  m.roughness = 1;
}

maybe<scalarT> triangle::meet(const ray& r) const
{
  auto n = norm(a - origin, b - origin, c - origin);
  auto th = -dot(r.v, n);
  if (th > 0) {
    auto d = dis(r.o, simplex2{a, b, c});
    if (d > 0) {
      auto t = d / th;
      auto e = r + t;
      if (in(e, simplex2{a,b,c})) {
        return just<scalarT>(d);
      }
    }
  }
  return nothing<scalarT>();
}

t_vector3 triangle::at(const point3& p) const
{ return t_vector3{p, norm(a - origin, b - origin, c - origin)}; }
