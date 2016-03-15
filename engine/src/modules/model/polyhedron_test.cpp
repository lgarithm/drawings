#include "polyhedron.h"

#include "solids.h"
#include "testing.h"

void test_1()
{
  auto R = 3.0;
  auto h = 4.0;
  auto of = oframe();
  auto b = cylinder_surface(R, of);
  auto u = Plane(t_vector3(of.o + .5 * h * of.f.Z, of.f.Z));
  auto d = Plane(t_vector3(of.o - .5 * h * of.f.Z, -of.f.Z));

  auto r = ray(origin + 3 * z_axis, -z_axis);

  auto t1 = b.meet(r);
  auto t2 = u.meet(r);
  auto t3 = d.meet(r);

  assert(!t1.just);
  assert(t2.just);
  assert(!t3.just);
}

void test_2()
{
  {
    auto c = new cylinder(3, 4);
    auto r = ray(origin + 3 * z_axis, -z_axis);
    auto i = c->intersect(r);
    assert(i.just);
    assert(i.it.d == 1);
  }
}

int main()
{
  test(1);
  test(2);
  return 0;
}
