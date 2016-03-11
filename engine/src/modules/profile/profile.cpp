#include "profile.h"

#include <cstdio>

#include <map>
#include <string>

#include "model.h"

using std::map;
using std::string;

void log_trace(const ray& r, int dep)
{
  printf("%d-th tracing ray{(%f, %f, %f) + (%f, %f, %f)t}\n",
         dep, r.o.x, r.o.y, r.o.z, r.v.x, r.v.y, r.v.z);
}

map<string, int> scope_logger::depth;

scope_logger::scope_logger(const string k) : k(k) { ++depth[k]; }

scope_logger::~scope_logger() { --depth[k]; }
