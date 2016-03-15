#include "builtin_examples.h"

#include <map>
#include <string>

#include "rey.h"

using std::map;
using std::string;

world* empty_scene() { return new world; }

world* default_test_scene()
{
  auto w = new world;
  *w += new Chessboard(3);
  return w;
}

world* test_board_1()
{
  auto w = new world;
  *w += new Chessboard;
  return w;
}

world* test_plane_1()
{
  auto w = new world;
  *w += new Plane(t_vector3{origin, z_axis});
  return w;
}

world* test_plane_2()
{
  auto w = new world;
  auto r1 = 2 * (x_axis + 2 * z_axis);
  auto r2 = 2 * (-x_axis + 2 * z_axis);
  *w += new Plane(t_vector3{origin - r1, norm(r1)});
  *w += new Plane(t_vector3{origin - r2, norm(r2)});
  return w;
}

world* single_ellipsoid()
{
  auto w = new world;
  *w += new ellipsoid(3,3,2);
  return w;
}

world* single_cylinder_surface()
{
  auto w = new world;
  *w += new cylinder_surface(2);
  return w;
}

world* single_cone_surface()
{
  auto w = new world;
  *w += new cone_surface(1 / 4.);
  return w;
}

world* test_ellipsoid()
{
  auto w = default_test_scene();
  auto e = new ellipsoid(3,3,2);
  e->of.o += 5 * z_axis;
  *w += e;
  return w;
}

world* test_ellipsoid_2()
{
  auto w = new world;
  auto e = new ellipsoid(3,3,2);
  auto f = new Plane(t_vector3{origin - 5 * z_axis, z_axis});
  f->m.reflection = .2;
  f->m.diffuse = yellow;

  *w += e;
  *w += f;
  return w;
}

world* test_cylinder_surface()
{
  auto w = default_test_scene();
  auto c1 = new cylinder_surface(3);
  auto c2 = new cylinder_surface(3);
  c1->of.o += -5 * x_axis;
  c2->of.o += 5 * x_axis;
  *w += c1;
  *w += c2;
  return w;
}

world* test_cylinder_surface_2()
{
  auto w = default_test_scene();
  auto c = new cylinder_surface(3);
  *w += c;
  return w;
}

world* test_cone()
{
  auto w = default_test_scene();
  auto c = new cone_surface(1. / 4);
  *w += c;
  return w;
}

world* test_cylinder()
{
  auto w = new world;
  *w += new cylinder(3, 3);
  return w;
}

world* test_cylinder_2()
{
  auto w = new world;
  auto of = oframe();
  *w += new cylinder(2, 4, of + 5 * z_axis);
  *w += new Floor;
  return w;
}

world* test_cylinder_3()
{
  auto w = new world;
  *w += new cylinder(12, 4, oframe());
  return w;
}

map<string, world_gen> examples()
{
  map<string, world_gen> mp;
  mp["empty"] = empty_scene;
  mp["test_board_1"] = test_board_1;
  mp["single_ellipsoid"] = single_ellipsoid;
  mp["single_cylinder_surface"] = single_cylinder_surface;
  mp["single_cone_surface"] = single_cone_surface;
  mp["test_plane_1"] = test_plane_1;
  mp["test_plane_2"] = test_plane_2;
  mp["ellipsoid"] = test_ellipsoid;
  mp["ellipsoid2"] = test_ellipsoid_2;
  mp["cylinder_surface"] = test_cylinder_surface;
  mp["cylinder_surface2"] = test_cylinder_surface_2;
  mp["cone"] = test_cone;
  mp["cylinder"] = test_cylinder;
  mp["cylinder2"] = test_cylinder_2;
  mp["cylinder3"] = test_cylinder_3;
  return mp;
}
