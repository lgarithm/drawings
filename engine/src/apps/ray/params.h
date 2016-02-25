#ifndef PARAMS_H
#define PARAMS_H

#include <vector>

#include "model.h"
#include "ray.h"

struct config
{
  display d;
  viewport v;

  camera cam;
  env lights;
  std::vector<object*> oo;

  bool t;
};

config def_config();
env def_env();

bool parse(int argc, const char * const argv[], config& cfg);
void usage(const char * name);
viewport center(double width, double height);

#endif  // PARAMS_H
