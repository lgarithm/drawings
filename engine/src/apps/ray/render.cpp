#include <cstdio>

#include <algorithm>
#include <memory>

#include "bmp.h"
#include "debug.h"
#include "display.h"
#include "model.h"
#include "params.h"
#include "ray.h"

using std::unique_ptr;

const int buffer_size = 3 * 2560 * 2560;
unsigned char buffer[buffer_size];

struct Floor : object
{
  bool intersect(const ray& r, intersection& cut) const /* override */
  {
    // d where r.start.z + d r.dir.z = 0
    if (r.dir.z != 0) {
      cut.d = - r.start.z / r.dir.z;
      if (cut.d < 0) return false;
      cut.r = r;
      cut.n = vec3(0,0,1);
      auto loc = r.advance(cut.d);
      int xx = int(loc.x) & 1;
      int yy = int(loc.y) & 1;
      if (xx ^ yy) {
	return false;
      }
      return true;
    }
    return false;
  }
};

int main(int argc, char* argv[])
{
  auto cfg = def_config();
  if (not parse(argc, argv, cfg)) {
    usage(argv[0]);
    return 0;
  }
  if (cfg.lights.lights.empty()) cfg.lights = def_env();

  {
    info(cfg.cam);
    printf("display %d X %d\n", cfg.d.width, cfg.d.height);
    printf("viewport [%f, %f] X [%f, %f]\n",
	   cfg.v.xr.lo, cfg.v.xr.hi, cfg.v.yr.lo, cfg.v.yr.hi);
    printf("%lu objects\n", cfg.oo.size() + 1);
    printf("%lu lights\n", cfg.lights.lights.size());
  }

  auto d = cfg.d;
  auto v = cfg.v;
  scene s;
  s.cam = cfg.cam;
  s.e = cfg.lights;

  s.w.objects.push_back(unique_ptr<object>(new Floor));
  for (int i=0; i < cfg.oo.size(); ++i) {
    s.w.objects.push_back(unique_ptr<object>(cfg.oo[i]));
  }

  if (not cfg.t) {
    printf("begin rednering...\n");
    render(s, v, d, buffer);
    printf("done\n");
    bmp_head head;
    head.init(d.width, d.height);
    write_bmp_file(head, buffer, "output.bmp");
  }
  return 0;
}
