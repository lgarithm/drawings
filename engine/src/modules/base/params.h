#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>

#include "model.h"
#include "ray.h"

static const int max_width = 4096;
static const int max_height = 4096;
static const int max_dep = 6;

struct config
{
  display d;
  viewport v;

  camera cam;
  env lights;
  std::vector<object*> oo;

  int dep;

  bool t;
  std::string outfile;

  config();
};

env def_env();

bool parse(int argc, const char * const argv[], config& cfg);
void usage(const char * name);
viewport center(double width, double height);

#endif  // PARAMS_H
