#include "model_surface.h"

#include <cassert>

#include <string>

#include "arith.h"
#include "debug.h"
#include "guard.h"

using std::string;

bool quadratic_surface::intersect(const ray& r, intersection& i) const
{
  const auto r_ = local(of, r);
  const auto e = equation(r_);
  assert(eval(e, 0) > 0);
  numericT t, t_;
  if (not min_positive_root(e, t)) return false;
  // assert_non_negative_zero(eval(e, t), "qs::" + string(__func__));
  auto p = r_ + t;
  auto q = n_at(p);
  i.n = global(of, t_vector3{p + 1e-6 * q, q});
  i.d = t;
  return true;
}


ellipsoid::ellipsoid(scalarT a, scalarT b, scalarT c) : a(a), b(b), c(c) { }

quad_eq ellipsoid::equation(const ray& r) const
{
  return (quad_eq{0, 0, -1} +
          sqr(1. / a * linear_eq{r.v.x, r.o.x}) +
          sqr(1. / b * linear_eq{r.v.y, r.o.y}) +
          sqr(1. / c * linear_eq{r.v.z, r.o.z}));
}

vector3 ellipsoid::n_at(const point3& p) const
{ return norm(p / vec3(a * a, b * b, c * c)); }


cylinder_surface::cylinder_surface(scalarT R) : R(R) { }

quad_eq cylinder_surface::equation(const ray& r) const
{
  return (quad_eq{0, 0, -R * R} +
          sqr(linear_eq{r.v.x, r.o.x}) +
          sqr(linear_eq{r.v.y, r.o.y}));
}

vector3 cylinder_surface::n_at(const point3& p) const
{ return norm(vec3(p.x, p.y, 0)); }


cone_surface::cone_surface(scalarT k) : k(k) { }

quad_eq cone_surface::equation(const ray& r) const
{
  return (sqr(linear_eq{r.v.x, r.o.x}) +
          sqr(linear_eq{r.v.y, r.o.y}) -
          sqr(k * linear_eq{r.v.z, r.o.z}));
}

vector3 cone_surface::n_at(const point3& p) const
{
  //  assert(p.z > 0);
  return norm(vec3(p.x, p.y, -k * k * p.z));
}
