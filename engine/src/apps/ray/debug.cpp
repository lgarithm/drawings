#include "debug.h"

#include <cstdio>

#include "model.h"

void pp(const point3& p) { printf("(%f, %f, %f)", p.x, p.y, p.z); }

void info(const camera& cam)
{
  printf("pos: ");
  pp(cam.pos);
  printf("\n");

  printf("forward: ");
  pp(cam.forward);
  printf("\n");

  printf("right: ");
  pp(cam.right);
  printf("\n");

  printf("up: ");
  pp(cam.up);
  printf("\n");
}
