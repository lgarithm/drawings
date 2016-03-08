#ifndef POLYHEDRON_H
#define POLYHEDRON_H

#include <vector>

#include "model.h"

struct cylinder_inf : simple_object
{
  oframe of;
  scalarT r;

  maybe<point3> intersect(const ray&) const;
  surface at(const point3&) const;
};

struct cylinder : object
{
  // t_vector t;
  oframe of;
  scalarT h;
  scalarT r;

  bool intersect(const ray&, intersection&) const /* override */;
};

struct polygon { std::vector<point2> vertices; };

scalarT area(const polygon&, const point2 = point2{0,0});
bool in(const point2&, const polygon&);

struct space_polygon : simple_object, polygon
{
  oframe of;

  space_polygon(const oframe&, const std::vector<point2>&);

  maybe<point3> intersect(const ray&) const;
  surface at(const point3&) const;
};

struct polyhedron : object
{
  std::vector<space_polygon> faces;

  bool intersect(const ray&, intersection&) const /* override */;

  //polyhedron();
};

polyhedron unit_cube(scalarT=1);

#endif  // POLYHEDRON_H
