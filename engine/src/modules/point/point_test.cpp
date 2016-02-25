#include "point.h"

#include <cassert>

void test_1()
{
  auto p = vec3(1,2,3);
  auto q = vec3(4,5,6);
  auto r = vec3(5,7,9);
  auto s = p + q;
  assert(r == s);
}

void test_2()
{
  auto p = vec3(1,1,1);
  p = norm(p);
  assert(len(p) == 1);

  auto q = vec3(0,0,0);
  q = norm(q);
  assert(len(q) == 0);
}

void test_3()
{
  auto x = vec3(1, 0, 0);
  auto y = vec3(0, 1, 0);
  auto z = vec3(0, 0, 1);
  assert(cross(x, y) == z);
  assert(cross(y, z) == x);
  assert(cross(z, x) == y);
}

int main()
{
  test_1();
  test_2();
  test_3();
  return 0;
}
