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

size_t save(const object* o, unsigned char *p)
{
  size_t s = sizeof(*o);
  return s;
}

void info(const world& w)
{
  unsigned char buffer[1024];
  for (auto& it : w.objects) {
    auto s = save(it.get(), buffer);
    printf("object{size : %lu}\n", s);
  }
}
