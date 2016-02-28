#include "debug.h"

#include <cstdio>

#include "model.h"

void pp(const point3& p) { printf("(%f, %f, %f)", p.x, p.y, p.z); }

void info(const camera& cam)
{
  printf("pos: ");
  pp(cam.of.o);
  printf("\n");
  {
    auto f = cam.of.f;
    printf(".: ");
    pp(f.Y);
    printf("\n");

    printf(">: ");
    pp(f.X);
    printf("\n");

    printf("^: ");
    pp(f.Z);
    printf("\n");
  }
  printf("near %lf\n", cam.near);
}
