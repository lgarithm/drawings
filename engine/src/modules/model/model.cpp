#include "model.h"

#include <cassert>
#include <cmath>
#include <cstdio>

#include <memory>
#include <vector>

#include "arith.h"
#include "color.h"
#include "guard.h"
#include "maybe.h"
#include "point.h"

using std::vector;
using std::unique_ptr;


bool operator<(const intersection& i, const intersection& j)
{ return i.d < j.d; }

maybe<intersection> nearest(const world& w, const ray& r)
{ return nearest(w.objects, r); }

maybe<intersection> simple_object::intersect(const ray& r) const
{
  auto t = meet(r);
  if (t.just) {
    auto s = at(r + t.it);
    s.n = s.n + 1e-6 * s.n.v;
    return just(intersection{s, t.it});
  }
  return nothing<intersection>();
}

void operator+=(world& w, object* po)
{ w.objects.push_back(unique_ptr<object>(po)); }
