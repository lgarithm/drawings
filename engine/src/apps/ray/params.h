#ifndef PARAMS_H
#define PARAMS_H

#include <vector>

#include "model.h"
#include "ray.h"

static const int max_width = 2560;
static const int max_height = 2560;

struct config
{
  display d;
  viewport v;

  camera cam;
  env lights;
  std::vector<object*> oo;

  int dep;

  bool t;
};

config def_config();
env def_env();

bool parse(int argc, const char * const argv[], config& cfg);
void usage(const char * name);
viewport center(double width, double height);

#endif  // PARAMS_H
