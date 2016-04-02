#ifndef LINEAR_H
#define LINEAR_H

#include "point.h"

struct frame
{
  vector3 X, Y, Z;

  frame();
  frame(const vector3&, const vector3&, const vector3&);
};

point3 local(const frame&, const point3&);
point3 global(const frame&, const point3&);

#endif  // LINEAR_H
