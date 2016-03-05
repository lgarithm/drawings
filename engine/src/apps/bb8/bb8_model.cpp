#include "bb8_model.h"

#include <cmath>
#include <memory>

#include <algorithm>

#include "color.h"
#include "maybe.h"
#include "model.h"
#include "primitives.h"

static auto const radian = 180 / M_PI;

using std::min;
using std::unique_ptr;

bb8_head::bb8_head(double size, const oframe& of) : size(size), of(of) {}

maybe<point3> bb8_head::intersect(const ray& r) const
{
  sphere s(size, of.o);
  auto mp = s.intersect(r);
  if (mp.just) {
    auto p = norm(local(of, mp.it));
    if (p.z >= 0) {
      return mp;
    }
  }
  return nothing<point3>();
}

surface bb8_head::at(const point3& p) const
{
  sphere sp(size, of.o);
  auto s = sp.at(p);
  auto q = norm(local(of, p));
  if (asin(q.z) * radian > 15) {
    s.m.diffuse = white;
  } else {
    s.m.diffuse = grey;
  }
  return s;
}

bb8_body::bb8_body(double size, const oframe& of) : size(size), of(of) {}

maybe<point3> bb8_body::intersect(const ray& r) const
{
  sphere s(size, of.o);
  auto mp = s.intersect(r);
  return mp;
}

surface bb8_body::at(const point3& p) const
{
  sphere sp(size, of.o);
  auto s = sp.at(p);

  auto q = norm(local(of, p));
  auto f1 = [&](const vector3& x)
    { return fabs(acos(dot(q, x)) - .5 * M_PI) * radian > 60; };
  auto f2 = [&](const vector3& x)
    { return fabs(acos(dot(q, x)) - .5 * M_PI) * radian > 70; };

  auto g1 = f1(x_axis) || f1(y_axis) || f1(z_axis);
  auto g2 = f2(x_axis) || f2(y_axis) || f2(z_axis);
  if (g1) {
    if (g2) {
      s.m.diffuse = grey;
    }
    else {
      s.m.diffuse = orange;
    }
  }
  s.m.reflection = .2;
  return s;
}

bb8::bb8(double size, const oframe& of) : head(.5 * size, of + size * z_axis),
                                          body(size, of) {}

bool bb8::intersect(const ray& r, intersection& i) const
{
  intersection j1, j2;
  bool f1 = body.simple_object::intersect(r, j1);
  bool f2 = head.simple_object::intersect(r, j2);
  if (not f1 and not f2) return false;
  if (not f1) {
    i = j2;
    return true;
  }
  if (not f2) {
    i = j1;
    return true;
  }
  i = min(j1, j2);
  return true;
}

world* bb8_example_1()
{
  auto w = new world;
  double size = 5;
  auto f = frame{norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis};
  auto gg = [&](vector3 p)
    {
      auto of = oframe{p + size * z_axis, f};
      w->objects.push_back(unique_ptr<object>(new bb8(size, of)));
    };
  gg(origin);

  w->objects.push_back(unique_ptr<object>(new Floor));
  return w;
}

world* bb8_example_2()
{
  auto w = new world;
  double size = 5;
  auto f = frame{norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis};
  auto gg = [&](vector3 p)
    {
      auto of = oframe{p + size * z_axis, f};
      w->objects.push_back(unique_ptr<object>(new bb8(size, of)));
    };

  double d = 15;
  for (auto x : {-1, 0, 1}) {
    for (auto y : {-1, 0, 1}) {
      gg(point3{d * x, d * y, 0});
    }
  }

  // w->objects.push_back(unique_ptr<object>(new Floor));
  w->objects.push_back(unique_ptr<object>(new Chessboard(5)));
  return w;
}
