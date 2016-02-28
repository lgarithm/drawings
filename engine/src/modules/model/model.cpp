#include "model.h"

#include <cmath>

#include <vector>

#include "arith.h"
#include "point.h"

using std::vector;

bool operator<(const intersection& i, const intersection& j) { return i.d < j.d; }

bool nearest(const world& w, const ray& r, intersection& i)
{
  vector<intersection> cuts;
  for (int idx=0; idx < w.objects.size(); ++idx) {
    const auto& it = w.objects[idx];
    intersection cut;
    if (it->intersect(r, cut)) {
      cuts.push_back(cut);
    }
  }
  if (not cuts.empty()) {
    i = cuts[0];
    for (int idx = 1; idx < cuts.size(); ++idx) {
      if (cuts[idx] < i) { i = cuts[idx]; }
    }
    return true;
  }
  return false;
}

bool Floor::intersect(const ray& r, intersection& cut) const
{
  if (r.v.z != 0) {
    cut.d = - r.o.z / r.v.z;
    if (cut.d <= 0) return false;
    cut.n = t_vector{r + cut.d, z_axis};
    cut.i = r.v;
    int xx = int(floor(cut.n.o.x)) & 1;
    int yy = int(floor(cut.n.o.y)) & 1;
    return xx == yy;
  }
  return false;
}

sphere::sphere(double size, const point3& pos): size(size), pos(pos) {}

bool sphere::intersect(const ray& r, intersection& cut) const
{
  auto ro = pos - r.o;
  auto v = dot(ro, r.v);
  if (v >= 0) {
    auto disc = size * size + v * v - dot(ro, ro);
    if (disc >= 0) {
      cut.d = v - sqrt(disc);
      cut.i = r.v;
      auto q = r + cut.d;
      cut.n = t_vector{q, q - pos};
      return true;
    }
  }
  return false;
}

triangle::triangle(const point3& a, const point3& b, const point3& c): a(a), b(b), c(c) {}

bool triangle::intersect(const ray& r, intersection& o) const
{
  auto n = norm(a,b,c);
  auto th = -dot(r.v, n);
  if (th > 0) {
    auto d = dis(r.o, simplex2{a, b, c});
    if (d > 0) {
      auto t = d / th;
      auto e = r + t;
      if (in(e, simplex2{a,b,c})) {
        o.n = t_vector{e, n};
        o.d = t;
        o.i = r.v;
        return true;
      }
    }
  }
  return false;
}
