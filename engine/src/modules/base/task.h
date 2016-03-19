#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

#include "display.h"
#include "model.h"
#include "primitives.h"  // For traisitive closure
#include "ray.h"
#include "view.h"

struct config
{
  display d;
  division dd;

  camera cam;
  env lights;
  world w;

  int dep;

  bool t;

  std::string outfile;

  int outfd;
  unsigned char * buffer;
  bool bmp_padding;

  bool use_thread;

  bool single;
  unsigned short i, j;

  std::vector<std::string> args;

  config();
};

#endif  // TASK_H
