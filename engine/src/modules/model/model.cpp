#include "model.h"

#include <cmath>

#include <vector>

#include "arith.h"
#include "color.h"
#include "maybe.h"
#include "point.h"

using std::vector;

camera::camera() : near(1), aov(45) {}

material::material() : diffuse(white), specular(grey), roughness(200),
                       reflection(.7) {}

bool operator<(const intersection& i, const intersection& j)
{ return i.d < j.d; }

bool nearest(const world& w, const ray& r, intersection& i)
{
  vector<intersection> cuts;
  for (const auto& it : w.objects) {
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

bool simple_object::intersect(const ray& r, intersection& i) const
{
  auto mp = intersect(r);
  if (mp.just) {
    auto s = at(mp.it);
    i.n = s.n;
    i.m = s.m;
    i.i = r.v;
    i.d = len(r.o - mp.it);
    return true;
  }
  return false;
}
