#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <memory>
#include <vector>
#include <utility>

#include "color.h"
#include "guard.h"  // For transitive closure
#include "material.h"
#include "maybe.h"
#include "point.h"
#include "linear.h"

typedef t_vector3 ray;

struct surface{ t_vector3 n; material m; };

struct intersection { surface s; scalarT d; };

bool operator<(const intersection&, const intersection&);

struct object
{ virtual maybe<intersection> intersect(const ray&) const = 0; };

struct simple_object : object
{
  maybe<intersection> intersect(const ray&) const override;
  virtual maybe<scalarT> meet(const ray&) const = 0;
  virtual surface at(const point3&) const = 0;
};

struct world{ std::vector<std::unique_ptr<object>> objects; };

void operator+=(world&, object*);
typedef world*(*world_gen)();
typedef std::map<std::string, world_gen> atlas;

template<typename T>
maybe<intersection> nearest(const std::vector<T>& oo, const ray& r)
{
  auto i = nothing<intersection>();
  for (const auto& it : oo) {
    auto j = it->intersect(r);
    if (j < i) i = j;
  }
  return i;
}

maybe<intersection> nearest(const world&, const ray&);

struct light{ point3 pos; color col; };
struct env{ std::vector<light> lights; };
typedef env*(*env_gen)();

#endif  // MODEL_H
