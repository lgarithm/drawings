#include "examples.h"

#include <memory>

#include "bb8_model.h"
#include "primitives.h"

using std::unique_ptr;

world* example_1()
{
  auto w = new world;
  {
    auto a = point3{-3, 1, 0};
    auto b = point3{3, 1, 0};
    auto c = point3{0, 5, 5};
    w->objects.push_back(unique_ptr<object>(new triangle(a,b,c)));
  }
  {
    double size = 5;
    auto p = point3{5,-5,0};
    auto f = frame{norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis};
    auto of = oframe{p + size * z_axis, f};
    w->objects.push_back(unique_ptr<object>(new bb8(size, of)));
  }
  return w;
}

world* example_2()
{
  auto w = new world;
  auto p = new Plane(t_vector{point3{-5, 0, 5}, x_axis});
  auto q = new Plane(t_vector{point3{5, 0, 5}, -x_axis});
  w->objects.push_back(unique_ptr<object>(new Chessboard));
  w->objects.push_back(unique_ptr<object>(p));
  w->objects.push_back(unique_ptr<object>(q));
  return w;
}
