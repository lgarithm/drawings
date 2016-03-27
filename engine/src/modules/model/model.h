#ifndef MODEL_H
#define MODEL_H

#include <map>
#include <memory>
#include <vector>
#include <utility>

#include "color.h"
#include "material.h"
#include "maybe.h"
#include "point.h"
#include "linear.h"

typedef t_vector3 ray;

struct neibourhood
{
  virtual vector3 at(const point3&) const = 0;
  virtual material mt(const point3&) const = 0;
};

struct intersection { const neibourhood* o; scalarT d; };

inline bool operator<(const intersection& i, const intersection& j)
{ return i.d < j.d; }

struct object { virtual maybe<intersection> intersect(const ray&) const = 0; };

typedef object*(*obj_gen)();

struct complex_object : object, neibourhood
{
  maybe<intersection> intersect(const ray&) const override;
  virtual maybe<scalarT> meet(const ray&) const = 0;
};

struct simple_object : complex_object
{
  material m;
  inline material mt(const point3&) const override { return m; }
};

struct world{ std::vector<std::unique_ptr<object>> objects; };

void operator+=(world&, object*);
typedef world*(*world_gen)();
typedef std::map<std::string, world_gen> atlas;

template<typename T> maybe<intersection> nearest(const T& oo, const ray& r)
{
  auto i = nothing<intersection>();
  for (const auto& it : oo) {
    auto j = it->intersect(r);
    if (j < i) i = j;
  }
  return i;
}

struct light{ point3 pos; color col; };
struct env{ std::vector<light> lights; };
typedef env*(*env_gen)();

#endif  // MODEL_H
