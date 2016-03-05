#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>

#include "display.h"
#include "model.h"
#include "primitives.h"  // For traisitive closure
#include "ray.h"

static const int max_width = 4096;
static const int max_height = 4096;
static const int max_dep = 6;

struct config
{
  display d;
  division dd;

  camera cam;
  env lights;
  std::vector<object*> oo;

  int dep;

  bool t;
  std::string outfile;

  bool use_thread;

  config();
};

env def_env();

bool parse(int argc, const char * const argv[], config& cfg);
void usage(const char * name);

#endif  // PARAMS_H
