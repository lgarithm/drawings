#include "linear.h"

#include <cassert>

#include "testing.h"

void test_1()
{
  oframe of;
  assert(of.o == origin);
  assert(of.f.X == x_axis);
  assert(of.f.Y == y_axis);
  assert(of.f.Z == z_axis);
}

void test_2()
{
  auto a = vec3(-1,0,0);
  auto b = vec3(0,-1,0);
  auto c = vec3(0,0,-1);
  auto f = frame{a,b,c};
  auto o = point3{1,1,1};
  auto of = oframe{o,f};
  auto p = point3{1,1,1};
  assert(true == (global(f, p) == point3{-1,-1,-1}));
  assert(true == (global(of, p) == point3{0,0,0}));
}

void test_3()
{
  auto of = oframe{point3{1,1,1}, frame{x_axis, y_axis, z_axis}};
  {
    auto p = local(of, point3{2,2,2});
    bool f = p == point3{1,1,1};
    assert(f);
  }
}

int main()
{
  test(1);
  test(2);
  test(3);
  return 0;
}
