#include "bb8_model.h"

#include <cassert>
#include <cmath>

#include <algorithm>

#include "rey.h"

using std::max;
using std::min;

template<typename T> T max3(const T& a, const T& b, const T& c)
{ return max(max(a, b), c); }

atlas bb8_examples()
{
  atlas mp;
  mp["example_1"] = bb8_example_1;
  mp["example_2"] = bb8_example_2;
  return mp;
}

bb8_head::bb8_head(double size, const oframe& of) : size(size), of(of) {}

maybe<scalarT> bb8_head::meet(const ray& r) const
{
  sphere s(size, of.o);
  auto t = s.meet(r);
  if (t.just) {
    auto p = local(of, r + t.it);
    if (p.z > 0) return t;
  }
  return nothing<scalarT>();
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

maybe<scalarT> bb8_body::meet(const ray& r) const
{
  sphere s(size, of.o);
  return s.meet(r);
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

maybe<intersection> bb8::intersect(const ray& r) const
{
  auto i1 = body.intersect(r);
  auto i2 = head.intersect(r);
  return min(i1, i2);
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
