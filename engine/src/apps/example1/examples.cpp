#include "examples.h"

#include <map>
#include <memory>
#include <string>

#include "bb8_model.h"
#include "rey.h"

using std::map;
using std::string;
using std::unique_ptr;

map<string, world_gen> examples()
{
  map<string, world_gen> mp;
  mp["example_1"] = example_1;
  mp["example_2"] = example_2;
  mp["test_room"] = test_room;
  return mp;
}

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
  auto p = new Plane(t_vector3{point3{-5, 0, 5}, x_axis});
  auto q = new Plane(t_vector3{point3{5, 0, 5}, -x_axis});
  w->objects.push_back(unique_ptr<object>(new Chessboard));
  w->objects.push_back(unique_ptr<object>(p));
  w->objects.push_back(unique_ptr<object>(q));
  return w;
}

world* test_room()
{
  auto w = new world;
  scalarT x = 100;
  scalarT y = 100;
  scalarT h = 30;
  auto lw = new Plane(t_vector3{origin - .5 * x * x_axis, x_axis});
  auto rw = new Plane(t_vector3{origin + .5 * x * x_axis, -x_axis});
  auto fw = new Plane(t_vector3{origin - .5 * y * y_axis, y_axis});
  auto bw = new Plane(t_vector3{origin + .5 * y * y_axis, -y_axis});
  auto c = new Plane(t_vector3{origin + h * z_axis, -z_axis});
  for (auto it : {lw, rw, fw, bw, c}) {
    it->m.reflection = .2;
  }
  lw->m.diffuse = blue;
  rw->m.diffuse = green;
  c->m.diffuse = color{.1, .1, .1};
  w->objects.push_back(unique_ptr<object>(new Chessboard));
  w->objects.push_back(unique_ptr<object>(lw));
  w->objects.push_back(unique_ptr<object>(rw));
  w->objects.push_back(unique_ptr<object>(fw));
  w->objects.push_back(unique_ptr<object>(bw));
  w->objects.push_back(unique_ptr<object>(c));
  return w;
}
