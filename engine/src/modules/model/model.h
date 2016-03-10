#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include "color.h"
#include "guard.h"  // For transitive closure
#include "material.h"
#include "maybe.h"
#include "point.h"
#include "linear.h"
#include "view.h"

typedef t_vector3 ray;

maybe<scalarT> r_dis(const t_vector3& n, const ray& r);

struct surface{ t_vector3 n; material m; };

struct intersection
{
  t_vector3 n;
  material m;
  double d;
};

bool operator<(const intersection&, const intersection&);

struct object
{ virtual bool intersect(const ray&, intersection&) const = 0; };

struct simple_object : object
{
  virtual maybe<point3> intersect(const ray&) const = 0;
  virtual surface at(const point3&) const = 0;
  bool intersect(const ray&, intersection&) const /* override */;
};

struct world{ std::vector<std::unique_ptr<object>> objects; };

typedef world*(*world_gen)();

template<typename T>
bool nearest(const std::vector<T>& oo, const ray& r, intersection& i)
{
  bool f = false;
  intersection cut;
  for (const auto& it : oo) {
    if (it->intersect(r, cut)) {
      if (not f or cut < i) {
        f = true;
        i = cut;
      }
    }
  }
  return f;
}

bool nearest(const world&, const ray&, intersection&);

struct light{ point3 pos; color col; };
struct env{ std::vector<light> lights; };

struct scene{ world w; env e; };

#endif  // MODEL_H
