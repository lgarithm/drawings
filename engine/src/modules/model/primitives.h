#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "linear.h"
#include "guard.h"
#include "maybe.h"
#include "model.h"
#include "point.h"

struct Plane : simple_object
{
  t_vector n;
  material m;

  Plane(const t_vector&);
  maybe<point3> intersect(const ray&) const /* override */;
  surface at(const point3&) const /* override */;
};

struct Floor : simple_object
{
  maybe<point3> intersect(const ray&) const /* override */;
  surface at(const point3&) const /* override */;
};

struct Chessboard : Floor
{
  double grid_size;

  Chessboard(double=1);
  surface at(const point3&) const /* override */;
};

struct Mirror : Floor { surface at(const point3&) const /* override */; };

struct sphere : simple_object
{
  double size;
  point3 pos;

  sphere(double, const point3&);
  maybe<point3> intersect(const ray&) const /* override */;
  surface at(const point3&) const /* override */;
};

struct triangle : simple_object
{
  point3 a,b,c;

  triangle(const point3&, const point3&, const point3&);
  maybe<point3> intersect(const ray&) const /* override */;
  surface at(const point3&) const /* override */;
};

#endif  // PRIMITIVE_H
