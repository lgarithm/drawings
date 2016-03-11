#include "builtin_examples.h"

#include <map>
#include <memory>
#include <string>

#include "rey.h"

using std::map;
using std::string;
using std::unique_ptr;

world* default_test_scene()
{
  auto w = new world;
  w->objects.push_back(unique_ptr<object>(new Chessboard(3)));
  return w;
}

world* test_ellipsoid()
{
  auto w = default_test_scene();
  auto e = new ellipsoid(3,3,2);
  e->of.o += 5 * z_axis;
  w->objects.push_back(unique_ptr<object>(e));
  return w;
}

world* test_ellipsoid_2()
{
  auto w = new world;
  auto e = new ellipsoid(3,3,2);
  auto f = new Plane(t_vector3{origin - 5 * z_axis, z_axis});
  f->m.reflection = .2;
  f->m.diffuse = yellow;

  w->objects.push_back(unique_ptr<object>(e));
  w->objects.push_back(unique_ptr<object>(f));
  return w;
}

world* test_cylinder()
{
  auto w = default_test_scene();
  auto c1 = new cylinder_surface(3);
  auto c2 = new cylinder_surface(3);
  c1->of.o += -5 * x_axis;
  c2->of.o += 5 * x_axis;
  w->objects.push_back(unique_ptr<object>(c1));
  w->objects.push_back(unique_ptr<object>(c2));
  return w;
}

world* test_cylinder_2()
{
  auto w = default_test_scene();
  auto c = new cylinder_surface(3);
  w->objects.push_back(unique_ptr<object>(c));
  return w;
}

world* test_cone()
{
  auto w = default_test_scene();
  auto c = new cone_surface(1. / 4);
  w->objects.push_back(unique_ptr<object>(c));
  return w;
}

map<string, world_gen> examples()
{
  map<string, world_gen> mp;
  mp["ellipsoid"] = test_ellipsoid;
  mp["ellipsoid2"] = test_ellipsoid_2;
  mp["cylinder"] = test_cylinder;
  mp["cylinder2"] = test_cylinder_2;
  mp["cone"] = test_cone;
  return mp;
}
