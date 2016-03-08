#include "profile.h"

#include <cstdio>

#include "model.h"

void log_trace(const ray& r, int dep)
{
  printf("%d-th tracing ray{(%f, %f, %f) + (%f, %f, %f)t}\n",
         dep, r.o.x, r.o.y, r.o.z, r.v.x, r.v.y, r.v.z);
}
