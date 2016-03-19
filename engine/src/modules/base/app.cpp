#include "app.h"

#include <cassert>
#include <cstdio>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <unistd.h>

#include "bmp.h"
#include "debug.h"
#include "display.h"
#include "logger.h"
#include "model.h"
#include "parallel.h"
#include "params.h"
#include "ray.h"
#include "utils.h"

using std::map;
using std::move;
using std::vector;
using std::string;
using std::unique_ptr;

namespace
{
  clogger lo;
  static const int buffer_size = 3 * max_width * max_height;
  // TODO : !!!!! separate per thread !!!!
  unsigned char g_buffer[buffer_size];
}  // namespace


void save(const char * name, const display& d, const unsigned char * buffer)
{
  bmp_head head;
  head.init(d.width, d.height);
  write_bmp_file(head, buffer, name);
}

void stream(int fd, const display& d, const unsigned char * buffer)
{
  bmp_head head;
  head.init(d.width, d.height);
  stream_bmp(head, buffer, fd);
}

void run(const config& cfg)
{
  if (cfg.t) return;
  engine e(cfg.dep, cfg.d);
  if (cfg.single) {
    auto g = e.rasterize(cfg.w, cfg.lights, cfg.cam, cfg.i, cfg.j);
    auto p = rgb(g);
    printf("pix[%d, %d] = (%f, %f, %f) # %02x %02x %02x | %d %d %d\n",
           cfg.j, cfg.i, expand_c(g), expand_c(p), expand_c(p));
    return ;
  }

  auto sch = scheduler{cfg.d};
  auto a = sch.divide();
  if (cfg.dd.m > 1 || cfg.dd.n > 1) a = sch.divide(cfg.dd.m, cfg.dd.n);
  size_t n = a.size();

  vector<result*> rs;
  vector<task*> tasks;
  unsigned char * p = g_buffer;
  if (cfg.buffer != nullptr) {
    p = cfg.buffer;
  }
  const unsigned char * buffer = p;
  for (int i=0; i < n; ++i) {
    const auto c = a[i];
    {
      with_c _(1, 43);
      printf("\rpreparing part %d/%zu : [%u, %u) X [%u, %u)", i + 1, n,
             c.w.l, c.w.r, c.h.l, c.h.r);
    }
    auto r = new result;
    rs.push_back(r);
    {
      r->p = p;
      p += 3 * size(c);
    }
    auto tsk = new task(e, cfg.w, cfg.lights, cfg.cam, c, r);
    tasks.push_back(tsk);
  }
  printf("\n");

  lo.log("begin rendering ...");
  run_tasks(tasks, cfg.use_thread);
  lo.log("end rendering ...");

  if (cfg.outfd > 0) {
    lo.log("streamming");
    if (!cfg.bmp_padding) {
      write(cfg.outfd, buffer, (unsigned) size(cfg.d) * 3);
    } else {
      stream(cfg.outfd, cfg.d, buffer);
    }
  } else if (cfg.dd.m > 1 && cfg.dd.n > 1) {
    for (auto it : rs) {
      char name[64];
      sprintf(name, "%s.%dX%d.part.[%d-%d)X[%d-%d).bmp", cfg.outfile.c_str(),
        cfg.dd.m, cfg.dd.n, it->c.w.l, it->c.w.r, it->c.h.l, it->c.h.r);
      lo.log("saving as " + string(name));
      save(name, from_clip(it->c), it->p);
    }
  } else {
    lo.log("saving as " + cfg.outfile);
    save(cfg.outfile.c_str(), cfg.d, buffer);
  }
  lo.log("done");
}

int app(int argc, char* argv[], const atlas& worlds, world_gen def)
{
  config cfg;
  if (not parse(argc, argv, cfg, worlds, def)) {
    usage(argv[0], worlds);
    return 0;
  }
  show_config(cfg);
  run(cfg);
  return 0;
}

int app(int argc, char* argv[]) { return app(argc, argv, atlas()); }
