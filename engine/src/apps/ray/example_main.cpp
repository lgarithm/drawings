#include <algorithm>
#include <memory>

#include "bmp.h"
#include "debug.h"
#include "display.h"
#include "examples.h"
#include "logger.h"
#include "model.h"
#include "params.h"
#include "ray.h"

using std::unique_ptr;

clogger lo;

static const int buffer_size = 3 * max_width * max_height;
unsigned char buffer[buffer_size];

int main(int argc, char* argv[])
{
  auto cfg = def_config();
  if (not parse(argc, argv, cfg)) {
    usage(argv[0]);
    return 0;
  }
  {
    printf("display %d X %d\n", cfg.d.width, cfg.d.height);
    printf("viewport [%f, %f] X [%f, %f]\n",
	   cfg.v.xr.lo, cfg.v.xr.hi, cfg.v.yr.lo, cfg.v.yr.hi);
    info(cfg.cam);
    printf("trace depth: %d\n", cfg.dep);
    //printf("%lu objects\n", cfg.oo.size());
    printf("%lu lights\n", cfg.lights.lights.size());
  }
  scene s;
  s.e = cfg.lights;
  unique_ptr<world> w(example_1());
  for (auto& it : w->objects) {
    s.w.objects.push_back(unique_ptr<object>(std::move(it)));
  }

  if (not cfg.t) {
    lo.log("begin rendering...");
    engine e(cfg.dep);
    e.render(s, cfg.cam, cfg.v, cfg.d, buffer);
    bmp_head head;
    head.init(cfg.d.width, cfg.d.height);
    lo.log("writting");
    write_bmp_file(head, buffer, "output.bmp");
    lo.log("done");
  }
  return 0;
}
