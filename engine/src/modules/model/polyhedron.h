#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>

#include "maybe.h"
#include "model.h"
#include "model_surface.h"
#include "primitives.h"
#include "solids.h"  // For transitive closure


struct polygon { std::vector<point2> vertices; };

scalarT area(const polygon&, const point2& _=pos2(0,0));
bool in(const point2&, const polygon&);

struct cylinder : object
{
  bound_cylinder_surface b;
  disc u, d;

  cylinder(scalarT, scalarT, const oframe=oframe());

  maybe<intersection> intersect(const ray&) const override;
};

struct space_polygon : simple_object, polygon
{
  oframe of;

  space_polygon(const oframe&, const std::vector<point2>&);

  maybe<scalarT> meet(const ray&) const override;
  vector3 at(const point3&) const override;
};

struct polyhedron : object
{
  std::vector<space_polygon> faces;

  maybe<intersection> intersect(const ray&) const override;

  //polyhedron();
};

polyhedron unit_cube(scalarT=1);

#endif  // POLYHEDRON_H
