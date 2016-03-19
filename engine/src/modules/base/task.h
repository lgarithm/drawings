#ifndef TASK_H
#define TASK_H

#include <string>
#include <vector>

#include "display.h"
#include "model.h"
#include "ray.h"
#include "view.h"

struct image_task
{
  std::vector<std::string> args;

  camera cam;
  display d;
  env lights;
  world w;
  int dep;

  bool single;
  unsigned short i, j;
  division dd;

  unsigned char * buffer;
  std::string outfile;
  int outfd;
  bool bmp_padding;

  bool t;
  bool use_thread;

  image_task();
};

#endif  // TASK_H
