#ifndef LINEAR_H
#define LINEAR_H

#include "point.h"

struct frame{ vector3 X, Y, Z; };
struct oframe{ point3 o; frame f; };
struct t_vector{ point3 o; vector3 v; };

point3 local(const frame&, const point3&);
point3 global(const frame&, const point3&);
point3 global(const oframe&, const point3&);
oframe observer(const point3&, const point3&, const vector3&);
point3 operator+(const t_vector&, pointT);

#endif  // LINEAR_H
