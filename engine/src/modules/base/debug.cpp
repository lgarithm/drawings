#include "debug.h"

#include <cstdio>

#include "model.h"
#include "params.h"

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

void show_config(const config& cfg)
{
  printf("display %d X %d\n", cfg.d.width, cfg.d.height);
  info(cfg.cam);
  printf("trace depth: %d\n", cfg.dep);
  printf("%lu objects\n", cfg.oo.size());
  printf("%lu lights\n", cfg.lights.lights.size());
}
