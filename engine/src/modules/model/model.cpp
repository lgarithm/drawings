#include "model.h"

#include <cmath>

#include <vector>

using std::vector;

point3 frame::trans(const point3& p)
{ return point3{dot(X, p), dot(Y, p), dot(Z, p)}; }

camera::camera(point3 pos, point3 lookAt): pos(pos)
{
  auto down = vec3(0.0, 0.0, -1.0);
  forward = norm(lookAt - pos);
  right = norm(cross(forward, down));
  up = norm(cross(forward, right));
}

point3 ray::advance(pointT d) const { return start + d * dir; }

bool intersection::operator<(const intersection& i) const { return d < i.d; }

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

sphere::sphere(double size, const point3& pos): size(size), pos(pos) {}

bool sphere::intersect(const ray& r, intersection& cut) const
{
  auto ro = pos - r.start;
  auto v = dot(ro, r.dir);
  if (v >= 0) {
    auto disc = size * size + v * v - dot(ro, ro);
    if (disc >= 0) {
      cut.d = v - sqrt(disc);
      cut.r = r;
      cut.n = r.advance(cut.d) - pos;
      return true;
    }
  }
  return false;
}

triangle::triangle(const point3& a, const point3& b, const point3& c): a(a), b(b), c(c) {}

bool triangle::intersect(const ray&, intersection& o) const
{

  return false;
}
