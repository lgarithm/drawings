#ifndef MODEL_SURFACE_H
#define MODEL_SURFACE_H

#include "arith.h"
#include "model.h"
#include "point.h"

struct algebraic_surface : object { };

struct quadratic_surface : algebraic_surface
{
  oframe of;
  bool intersect(const ray&, intersection&) const /* override */;

  virtual quad_eq equation(const ray&) const = 0;
  virtual vector3 n_at(const point3&) const = 0;
};

struct ellipsoid : quadratic_surface
{
  scalarT a, b, c;

  ellipsoid(scalarT, scalarT, scalarT);
  quad_eq equation(const ray&) const /* override */;
  vector3 n_at(const point3&) const /* override */;
};

struct cylinder_surface : quadratic_surface
{
  scalarT R;

  cylinder_surface(scalarT);
  quad_eq equation(const ray&) const /* override */;
  vector3 n_at(const point3&) const /* override */;
};

// struct cone_surface : quadratic_surface { };

#endif  // MODEL_SURFACE_H
