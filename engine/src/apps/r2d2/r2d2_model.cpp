#include "r2d2_model.h"

#include "rey.h"


r2d2_head::r2d2_head(scalarT r, const oframe& of) : sphere(r, of.o), of(of) { }

maybe<scalarT> r2d2_head::meet(const ray& r) const
{
  const auto t = sphere::meet(r);
  const auto f = [&](scalarT d){
    auto z = local(of, r + d).z;
    return z > 0 ? just(d) : nothing<scalarT>();
  };
  return inject(t, f);
}

surface r2d2_head::at(const point3& p) const
{
  auto s = sphere::at(p);
  auto q = norm(local(of, p));
  auto g = asin(q.z) * radian;
  if (g > 15) {
    if (g > 50 && g < 70) {
      s.m.diffuse = blue;
    } else {
      s.m.diffuse = white;
    }
  } else {
    s.m.diffuse = blue;
  }
  return s;
}


r2d2_body::r2d2_body(scalarT r, scalarT h, const oframe& of)
  : bound_cylinder_surface(r, h, of) { }

surface r2d2_body::at(const point3& p) const
{
  auto s = bound_cylinder_surface::at(p);
  auto q = local(of, p);
  auto d1 = atan2(q.y, q.x) * radian;
  if (-2 < q.z && q.z < 1.5) {
    if (90 - 15 < d1 && d1 < 90 + 15) {
      s.m.diffuse = blue;
    }
  } else
  if ((1.8 < q.z && q.z < 2.4) || (2.6 < q.z && q.z < 3.2)) {
    if (90 - 30 < d1 && d1 < 90 + 30) {
      s.m.diffuse = blue;
    }
  }
  return s;
}


r2d2::r2d2(scalarT r, scalarT h, const oframe& of)
  : head(r, of + .5 * h * of.f.Z)
  , body(r, h, of)
  , bottom(r, t_vector3(of.o - .5 * h * of.f.Z, -of.f.Z))
  { }

maybe<intersection> r2d2::intersect(const ray& r) const
{
  auto i1 = body.intersect(r);
  auto i2 = head.intersect(r);
  auto i3 = bottom.intersect(r);
  return min3(i1, i2, i3);
}

namespace {

world* default_test_scene()
{
  auto w = new world;
  *w += new Floor;
  return w;
}

world* test_r2d2_1()
{
  auto w = default_test_scene();
  auto h = 7;
  auto r = 3;
  auto of = oframe(origin, frame(-x_axis, -y_axis, z_axis));
  of = of + .5 * h * of.f.Z;
  *w += new r2d2(r, h, of);
  return w;
}

}  // namespace

atlas r2d2_examples()
{
  map<string, world_gen> mp;
  mp["test_r2d2_1"] = test_r2d2_1;
  return mp;
}
