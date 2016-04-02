#include "view.h"

#include "testing.h"

void test_1()
{
  auto t = [](const camera& c, scalarT d){
    auto p = local(c.of, origin);
    assert(p.x == 0);
    assert(p.z == 0);
    assert(p.y == d);
  };
  t(camera::top(99), 99);
  t(camera::bottom(99), 99);
  t(camera::front(99), 99);
  t(camera::back(99), 99);
  t(camera::left(99), 99);
  t(camera::right(99), 99);
}

int main()
{
  test(1);
  return 0;
}
