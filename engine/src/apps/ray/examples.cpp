#include "examples.h"

#include <memory>

using std::unique_ptr;

world* example_1()
{
  auto w = new world;
  auto a = point3{-1, -1, 0};
  auto b = point3{1, -1, 0};
  auto c = point3{0, 1, 0};

  w->objects.push_back(unique_ptr<object>(new triangle(a,b,c)));
  //w->objects.push_back(unique_ptr<object>(new Floor));
  return w;
}
