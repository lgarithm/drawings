#include "builtin_examples.h"

#include "rey.h"

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
  *w += new plane(t_vector3{origin, z_axis});
  return w;
}

world* test_plane_2()
{
  auto w = new world;
  auto r1 = 2 * (x_axis + 2 * z_axis);
  auto r2 = 2 * (-x_axis + 2 * z_axis);
  *w += new plane(t_vector3{origin + -r1, norm(r1)});
  *w += new plane(t_vector3{origin + -r2, norm(r2)});
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
  e->of.o = e->of.o + 5 * z_axis;
  *w += e;
  return w;
}

world* test_ellipsoid_2()
{
  auto w = new world;
  auto e = new ellipsoid(3,3,2);
  auto f = new plane(t_vector3{origin + -5 * z_axis, z_axis});
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
  c1->of.o = c1->of.o + -5 * x_axis;
  c2->of.o = c2->of.o + 5 * x_axis;
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

static const auto examples_ = atlas({
    {"empty", empty_scene},
    {"test_board_1", test_board_1},
    {"single_ellipsoid", single_ellipsoid},
    {"single_cylinder_surface", single_cylinder_surface},
    {"single_cone_surface", single_cone_surface},
    {"test_plane_1", test_plane_1},
    {"test_plane_2", test_plane_2},
    {"ellipsoid", test_ellipsoid},
    {"ellipsoid2", test_ellipsoid_2},
    {"cylinder_surface", test_cylinder_surface},
    {"cylinder_surface2", test_cylinder_surface_2},
    {"cone", test_cone},
    {"cylinder", test_cylinder},
    {"cylinder2", test_cylinder_2},
    {"cylinder3", test_cylinder_3},
  });

atlas examples() { return examples_; }
