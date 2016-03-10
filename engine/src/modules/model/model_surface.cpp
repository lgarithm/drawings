#include "model_surface.h"

#include "arith.h"
#include "guard.h"

bool quadratic_surface::intersect(const ray& r, intersection& i) const
{
  const auto r_ = local(of, r);
  const auto e = equation(r_);
  numericT t, t_;
  if (not min_positive_root(e, t)) return false;
  t -= 5e-5;
  assert_non_negative_zero(eval(e, t), __func__);
  auto p = r_ + t;
  i.n = global(of, t_vector3{p, n_at(p)});
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
