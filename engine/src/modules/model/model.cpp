#include "model.h"

#include <memory>

#include "maybe.h"
#include "point.h"

using std::unique_ptr;

maybe<intersection> complex_object::intersect(const ray& r) const
{
  auto t = meet(r);
  if (t.just) { return just(intersection{this, t.it}); }
  return nothing<intersection>();
}

void operator+=(world& w, object* po)
{ w.objects.push_back(unique_ptr<object>(po)); }
