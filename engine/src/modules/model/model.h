#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include "color.h"
#include "point.h"
#include "linear.h"

struct camera
{
  oframe of;
  pointT near;
  // TODO: AOV
  // TODO: pointT far;
};

typedef t_vector ray;

struct itsec
{
  t_vector t;
  vector3 in;

  double alpha;
  double refraction_ratio;

  double reflect;
  double diffuse;
};

struct intersection
{
  t_vector n;
  vector3 i;
  double d;
};

struct object{ virtual bool intersect(const ray&, intersection&) const = 0; };
struct world{ std::vector<std::unique_ptr<object>> objects; };
bool nearest(const world&, const ray&, intersection&);

struct Floor : object
{ bool intersect(const ray&, intersection&) const /* override */; };

struct sphere : object
{
  double size;
  point3 pos;
  sphere(double, const point3&);
  bool intersect(const ray&, intersection&) const /* override */;
};

struct triangle : object
{
  point3 a,b,c;
  triangle(const point3&, const point3&, const point3&);
  bool intersect(const ray&, intersection&) const /* override */;
};

struct light{ point3 pos; color col; };
struct env{ std::vector<light> lights; };

struct scene{ world w; env e; };

#endif  // MODEL_H
