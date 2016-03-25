#include "model.h"

#include <cassert>
#include <cmath>
#include <cstdio>

#include <memory>
#include <vector>

#include "arith.h"
#include "color.h"
#include "maybe.h"
#include "point.h"

using std::vector;
using std::unique_ptr;


bool operator<(const intersection& i, const intersection& j)
{ return i.d < j.d; }

maybe<intersection> nearest(const world& w, const ray& r)
{ return nearest(w.objects, r); }

maybe<intersection> complex_object::intersect(const ray& r) const
{
  auto t = meet(r);
  if (t.just) {
    const auto p = r + t.it;
    auto n = at(p);
    n = n + 1e-6 * n.v;
    return just(intersection{surface{n, mt(p)}, t.it});
  }
  return nothing<intersection>();
}

material simple_object::mt(const point3&) const { return m; }

void operator+=(world& w, object* po)
{ w.objects.push_back(unique_ptr<object>(po)); }
