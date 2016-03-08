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
  auto w = new world;
  auto e = new ellipsoid(3,3,2);
  auto f = new Plane(t_vector{origin - 5 * z_axis, z_axis});
  f->m.reflection = .2;
  f->m.diffuse = yellow;

  w->objects.push_back(unique_ptr<object>(e));
  w->objects.push_back(unique_ptr<object>(f));
  return w;
}

map<string, world_gen> examples()
{
  map<string, world_gen> mp;
  mp["ellipsoid"] = test_ellipsoid;
  return mp;
}
