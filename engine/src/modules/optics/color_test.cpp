#include "color.h"

#include "testing.h"

void test_1()
{
  auto c = color{.1, .1, .1};
  auto d = color{.5, .5, .5};
  c += d;
  assert(c.r == .6);
  assert(c.g == .6);
  assert(c.b == .6);
}

int main()
{
  test(1);
  return 0;
}
