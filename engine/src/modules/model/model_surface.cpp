#include "model_surface.h"

#include "arith.h"

ellipsoid::ellipsoid(scalarT a, scalarT b, scalarT c) : a(a), b(b), c(c) { }

bool ellipsoid::intersect(const ray& r, intersection& i) const
{
  auto e = (quad_eq{0, 0, -1} +
            sqr(1. / a * linear_eq{r.v.x, r.o.x}) +
            sqr(1. / b * linear_eq{r.v.y, r.o.y}) +
            sqr(1. / c * linear_eq{r.v.z, r.o.z}));
  numericT t, t_;
  auto n = positive_roots(e, t, t_);
  if (n == 0) return false;
  auto nm = vec3(0,0,1);
  auto p = r + t;
  auto q = norm(p / vec3(a * a, b * b, c * c));
  i.n = t_vector{p, q};
  i.d = t;
  return true;
}
