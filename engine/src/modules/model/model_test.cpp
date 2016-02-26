#include "model.h"

#include <cassert>
#include <cmath>

void test_1()
{
  intersection i;
  auto s = sphere(1, point3{0, 0, 0});

  {
    auto r = ray{point3{0, 0, 2}, norm(vec3(0, 0, -1))};
    bool f = s.intersect(r, i);
    assert(f);
    assert(i.d == 1);
  }

  {
    auto r = ray{point3{0, 0, sqrt(2.0)}, norm(vec3(1 - 1e-9, 0, -1))};
    bool f = s.intersect(r, i);
    assert(f);
  }

  {
    auto r = ray{point3{0, 0, sqrt(2.1)}, norm(vec3(1, 0, -1))};
    bool f = s.intersect(r, i);
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
    auto r = ray{point3{0,0,0}, norm(vec3(1,1,1))};
    bool f = t.intersect(r, i);
    assert(f);
  }
}

int main()
{
  test_1();
  // test_2();
  return 0;
}
