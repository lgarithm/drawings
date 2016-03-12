#include "bb8_model.h"

#include <cmath>

#include <algorithm>
#include <map>
#include <string>

#include "rey.h"

static auto const radian = 180 / M_PI;

using std::map;
using std::max;
using std::min;
using std::string;

template<typename T> T max3(const T& a, const T& b, const T& c)
{ return max(max(a, b), c); }

map<string, world_gen> bb8_examples()
{
  map<string, world_gen> mp;
  mp["example_1"] = bb8_example_1;
  mp["example_2"] = bb8_example_2;
  return mp;
}

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
  auto g = asin(q.z) * radian;
  if (g > 10) {
    if (g > 50 && g < 60) {
      s.m.diffuse = orange;
    } else {
      s.m.diffuse = white;
    }
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

  const auto q = norm(local(of, p));
  const auto r = point3{fabs(q.x), fabs(q.y), fabs(q.z)};
  auto th = acos(max3(dot(r, x_axis), dot(r, y_axis), dot(r, z_axis))) * radian;

  if (th < 30) {
    if (th < 20) {
      s.m.diffuse = grey;
    } else {
      s.m.diffuse = orange;
    }
  } else {
    /*
    static const auto eps = 5e-3;
    if (fabs(q.x) <  eps|| fabs(q.y) < eps || fabs(q.z) < eps) {
      s.m.diffuse = grey;
    }//*/
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
      *w += new bb8(size, of);
    };
  gg(origin);
  *w += new Floor;
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
      *w += new bb8(size, of);
    };

  double d = 15;
  for (auto x : {-1, 0, 1}) {
    for (auto y : {-1, 0, 1}) {
      gg(point3{d * x, d * y, 0});
    }
  }
  *w += new Chessboard(5);
  return w;
}
