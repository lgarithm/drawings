#ifndef MODEL_SURFACE_H
#define MODEL_SURFACE_H

#include "model.h"

struct algebraic_surface : object
{

};

struct quadratic_surface : algebraic_surface
{

};

struct ellipsoid : quadratic_surface
{
  scalarT a, b, c;

  ellipsoid(scalarT a, scalarT b, scalarT c);
  bool intersect(const ray&, intersection&) const;
};

#endif  // MODEL_SURFACE_H
