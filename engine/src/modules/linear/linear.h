#ifndef LINEAR_H
#define LINEAR_H

#include "point.h"

struct t_vector2{ point2 o; vector2 v; };
struct t_vector3{ point3 o; vector3 v; };

struct frame
{
  vector3 X, Y, Z;

  frame();
  frame(const vector3&, const vector3&, const vector3&);
};

struct oframe
{
  point3 o;
  frame f;

  oframe();
  oframe(const point3&, const frame&);
};

point3 local(const frame&, const point3&);
point3 global(const frame&, const point3&);

point3 local(const oframe&, const point3&);
point3 global(const oframe&, const point3&);

t_vector3 local(const oframe&, const t_vector3&);
t_vector3 global(const oframe&, const t_vector3&);

oframe observer(const point3&, const point3&, const vector3&);

oframe operator+(const oframe&, const vector3&);
point3 operator+(const t_vector3&, scalarT);

#endif  // LINEAR_H
