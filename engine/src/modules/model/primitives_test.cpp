#include "primitives.h"

#include <cassert>
#include <cmath>

#include "model.h"
#include "testing.h"

void test_1()
{
  intersection i;
  auto s = sphere(1, point3{0, 0, 0});
  {
    auto r = ray{point3{0, 0, 2}, norm(vec3(0, 0, -1))};
    bool f = s.simple_object::intersect(r, i);
    assert(f);
    assert(i.d == 1);
  }
  {
    auto r = ray{point3{0, 0, sqrt(2.0)}, norm(vec3(1 - 1e-9, 0, -1))};
    bool f = s.simple_object::intersect(r, i);
    assert(f);
  }
  {
    auto r = ray{point3{0, 0, sqrt(2.1)}, norm(vec3(1, 0, -1))};
    bool f = s.simple_object::intersect(r, i);
    assert(not f);
  }
}

void test_2()
{
  intersection i;
  auto a = point3{1,0,0};
  auto b = point3{0,1,0};
  auto c = point3{0,0,1};
  auto t = triangle(a,b,c);
  {
    auto r = ray{point3{1,1,1}, norm(vec3(-1,-1,-1))};
    bool f = t.simple_object::intersect(r, i);
    assert(f);
  }
}

int main()
{
  test(1);
  test(2);
  return 0;
}
