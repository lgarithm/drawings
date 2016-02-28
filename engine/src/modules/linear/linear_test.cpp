#include "linear.h"

#include <cassert>

#include "testing.h"

void test_1()
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

int main()
{
  test(1);
  return 0;
}
