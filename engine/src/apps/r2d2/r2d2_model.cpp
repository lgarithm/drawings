#include "r2d2_model.h"

#include "model.h"
#include "rey.h"

#define inject(m, f) (m.just ? f(m.it) : m)

struct r2d2_head : sphere
{
  oframe of;

  r2d2_head(scalarT r, const oframe& of) : sphere(r, of.o), of(of) { }

  maybe<scalarT> meet(const ray& r) const override
  {
    const auto t = sphere::meet(r);
    const auto f = [&](scalarT d){
      auto z = local(of, r + d).z;
      return z > 0 ? just(d) : nothing<scalarT>();
    };
    return inject(t, f);
  }
};

struct r2d2_body : bound_cylinder_surface
{
  r2d2_body(scalarT r, scalarT h, const oframe& of)
    : bound_cylinder_surface(r, h, of) { }
};

struct r2d2 : object
{
  r2d2_head head;
  r2d2_body body;
  disc bottom;

  r2d2(scalarT r, scalarT h, const oframe& of=oframe())
    : head(r, of + .5 * h * of.f.Z)
    , body(r, h, of)
    , bottom(r, t_vector3(of.o - .5 * h * of.f.Z, -of.f.Z))
    { }

  maybe<intersection> intersect(const ray& r) const
  {
    auto i1 = body.intersect(r);
    auto i2 = head.intersect(r);
    auto i3 = bottom.intersect(r);
    return min3(i1, i2, i3);
  }
};

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
  oframe of;
  of = of + .5 * h * of.f.Z;
  *w += new r2d2(r, h, of);
  return w;
}

atlas examples()
{
  map<string, world_gen> mp;
  mp["test_r2d2_1"] = test_r2d2_1;
  return mp;
}
