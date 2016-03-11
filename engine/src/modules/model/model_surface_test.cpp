#include "model_surface.h"

#include <cassert>
#include <cmath>

#include "arith.h"
#include "debug.h"
#include "testing.h"

void test_1()
{
  auto c = cone_surface{1};
  auto n = c.n_at(vec3(1, 1, sqrt(2)));
  auto z = n - norm(vec3(1, 1, -sqrt(2)));
  printf("(%f, %f, %f)\n", expand_v(z));
  assert_eq(z.x, 0);
  assert_eq(z.y, 0);
  assert_eq(z.y, 0);
}

int main()
{
  test(1);
  return 0;
}
