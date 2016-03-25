#include <cmath>

#include <type_traits>

#include "rey.h"

#define CONS(c) c(scalarT size, const point3& pos) : sphere(size, pos) { }

struct billiard : sphere
{
  CONS(billiard)

  material mt(const point3& p) const override
  {
    auto q = norm(p - pos);
    auto g = asin(q.z) * radian;
    if (fabs(g) > 35) {
      material m;
      m.diffuse = white;
      return m;
    } else {
      auto h = acos(dot(q, y_axis)) * radian - 90;
      if (fabs(h) > 70) {
        material m;
        m.diffuse = white;
        return m;
      } else {
        return m;
      }
    }
  }
};

struct Billiard : sphere
{
  CONS(Billiard)

  material mt(const point3& p) const override
  {
    auto q = norm(p - pos);
    auto h = acos(dot(q, y_axis)) * radian - 90;
    if (fabs(h) > 70) {
      material m;
      m.diffuse = white;
      return m;
    } else {
      return m;
    }
  }
};

world* example_1()
{
  auto w = new world;
  {
    auto f = new Floor;
    f->m.diffuse = .2 * red + .9 * green + .2 * blue;
    *w += f;
  }
  const auto r = 2;
  const auto h = sqrt(3) * r;
  auto f = [&](scalarT x, scalarT y, const color& c){
    auto s = new billiard(r, pos3(x, y, r));
    s->m.diffuse = c;
    *w += s;
  };
  auto g = [&](scalarT x, scalarT y, const color& c){
    auto s = new Billiard(r, pos3(x, y, r));
    s->m.diffuse = c;
    *w += s;
  };

  f(r, 0, yellow);
  f(-r, 0, blue);
  f(0, -h, red);
  f(-2 * r, -h, orange);

  g(5 * r, 0, yellow);
  g(3 * r, 0, blue);
  g(4 * r, -h, red);
  g(2 * r, -h, orange);

  return w;
}

static const auto examples = atlas({
    {"example_1", example_1},
  });

int main()
{
  static const char * argv[] = {
    "billiard",
    "-a", "40",
    "-c", "((5, -30, 25), (0,0,0), (0,0,1))",
    "-d", "4kf",
    "-l", "light((0,0,50), (.2, .2, .2))",
    "-l", "light((-20,-20,1), (.2, .2, .2))",
    "-l", "light((20,20,1), (.2, .2, .2))",
    "-l", "light((-20,20,1), (.2, .2, .2))",
    "-l", "light((20,-20,1), (.2, .2, .2))",
    "-l", "light((-20,-20,10), (.2, .2, .2))",
    "-l", "light((20,20,10), (.2, .2, .2))",
    "-l", "light((-20,20,10), (.2, .2, .2))",
    "-l", "light((20,-20,10), (.2, .2, .2))",
    "example_1",
    "-p",
  };
  const auto argc = std::extent<decltype(argv)>::value;
  return app(argc, argv, examples);
}
