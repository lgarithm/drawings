#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include "color.h"
#include "guard.h"  // For transitive closure
#include "maybe.h"
#include "point.h"
#include "linear.h"

struct camera
{
  oframe of;
  scalarT near;
  scalarT aov;
  // TODO: scalarT far;
  // TODO: scalarT aspect = 1;

  camera(const oframe=top);

  static const oframe top;
  static const oframe front;
};

typedef t_vector ray;

maybe<scalarT> r_dis(const t_vector& n, const ray& r);

struct material
{
  color diffuse;
  color specular;
  unsigned char roughness;
  colorT reflection;

  material();

  // TODO
  // static const material
};

struct surface{ t_vector n; material m; };

struct intersection
{
  t_vector n;
  vector3 i;
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
