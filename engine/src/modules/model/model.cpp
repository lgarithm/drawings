#include "model.h"

#include <cmath>

#include <vector>

#include "arith.h"
#include "color.h"
#include "guard.h"
#include "maybe.h"
#include "point.h"

using std::vector;

const oframe camera::top = oframe{origin + z_axis, origin, y_axis};
const oframe camera::front = oframe{origin - y_axis, origin, z_axis};

camera::camera(const oframe of) : of(of), near(1), aov(45) {}

maybe<scalarT> r_dis(const t_vector& n, const ray& r)
{
  assert_unit(r.v, __func__);
  auto c = dot(n.v, r.v);
  if (c < 0) {
    auto l = dot(n.v, n.o - r.o);
    if (l < 0) return just<scalarT>(l / c);
  }
  return nothing<scalarT>();
}

bool operator<(const intersection& i, const intersection& j)
{ return i.d < j.d; }

bool nearest(const world& w, const ray& r, intersection& i)
{ return nearest(w.objects, r, i); }

bool simple_object::intersect(const ray& r, intersection& i) const
{
  auto mp = intersect(r);
  if (mp.just) {
    auto s = at(mp.it);
    i.n = s.n;
    i.m = s.m;
    i.d = len(r.o - mp.it);
    return true;
  }
  return false;
}
