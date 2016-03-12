#include "app.h"

#include <cassert>
#include <cstdio>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

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
  unsigned char buffer[buffer_size];
  unsigned char* buffers[4096];

  struct scene{ world w; env e; };
}  // namespace


void save(const char * name, const display& d, const unsigned char * buffer)
{
  bmp_head head;
  head.init(d.width, d.height);
  write_bmp_file(head, buffer, name);
}

void run(const config& cfg, const scene& s)
{
  if (cfg.t) return;
  engine e(cfg.dep, cfg.d);
  if (cfg.single) {
    auto g = e.rasterize(s.w, s.e, cfg.cam, cfg.i, cfg.j);
    auto p = rgb(g);
    printf("pix[%d, %d] = (%f, %f, %f) # %02x %02x %02x | %d %d %d\n",
           cfg.j, cfg.i, expand_c(g), expand_c(p), expand_c(p));
    return ;
  }

  auto sch = scheduler{cfg.d};
  auto a = sch.divide();
  if (cfg.dd.m > 1 || cfg.dd.n > 1) a = sch.divide(cfg.dd.m, cfg.dd.n);
  size_t n = a.size();

  lo.log("begin rendering ...");

  vector<task*> tasks;
  vector<result*> rs;
  unsigned char * p = buffer;
  for (int i=0; i < n; ++i) {
    const auto c = a[i];
    char msg[64];
    sprintf(msg, "rendering part %d/%zu : [%u, %u) X [%u, %u)", i + 1, n,
            c.w.l, c.w.r, c.h.l, c.h.r);
    lo.log(msg);
    {
      buffers[i] = p;
      p += 3 * size(c);
    }
    auto r = new result;
    auto tsk = new task(e, s.w, s.e, cfg.cam, c, buffers[i], r);
    rs.push_back(r);
    tasks.push_back(tsk);
  }

  run_tasks(tasks, cfg.use_thread);

  if (cfg.dd.m > 1 && cfg.dd.n > 1) {
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

int app(int argc, char* argv[], map<string, world_gen> worlds, world_gen def)
{
  config cfg;
  if (not parse(argc, argv, cfg)) {
    usage(argv[0]);
    return 0;
  }
  show_config(cfg);

  scene s;
  s.e = cfg.lights;

  auto name = cfg.args.empty() ? "" : cfg.args[0];
  auto fn = get<string, world_gen>(worlds, name, def);
  if (fn != nullptr) {
    unique_ptr<world> w(fn());
    for (auto& it : w->objects) {
      lo.log("add 1 object from scene", clogger::RED);
      s.w += it.get();
      it.release();
    }
  }
  for (auto it : cfg.oo) {
    lo.log("add object from cfg", clogger::RED);
    s.w += it;
  }
  info(s.w);
  run(cfg, s);
  return 0;
}

int app(int argc, char* argv[])
{ return app(argc, argv, map<string, world_gen>()); }
