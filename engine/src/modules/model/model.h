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
  scalarT near;
  // TODO: AOV
  // TODO: scalarT far;
};

typedef t_vector ray;

struct itsec
{
  t_vector t;
  vector3 in;
};

struct material
{
  color diffuse;
  color specular;
  unsigned char roughness;
  double reflection;
  material();
};

struct intersection
{
  t_vector n;
  vector3 i;
  material m;
  double d;
  // intersection();
};

bool operator<(const intersection& i, const intersection& j);

struct object{ virtual bool intersect(const ray&, intersection&) const = 0; };
struct world{ std::vector<std::unique_ptr<object>> objects; };
bool nearest(const world&, const ray&, intersection&);

struct Floor : object
{ bool intersect(const ray&, intersection&) const /* override */; };

struct Chessboard : object
{ bool intersect(const ray&, intersection&) const /* override */; };

struct Mirror : object
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
