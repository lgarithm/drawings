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

void create_render_tasks(const image_task& img_tsk, const engine& e,
                         const vector<clip>& a, unsigned char * buffer,
                         vector<task*>& ts, vector<result*>& rs)
{
  unsigned char * p = buffer;
  auto idx = 0;
  for (auto c : a) {
    {
      with_c _(1, 43);
      printf("\rpreparing part %d/%zu : [%u, %u) X [%u, %u)", ++idx, a.size(),
             c.w.l, c.w.r, c.h.l, c.h.r);
    }
    auto r = new result;
    rs.push_back(r);
    {
      r->p = p;
      p += 3 * size(c);
    }
    auto tsk = new task(e, img_tsk.w, img_tsk.lights, img_tsk.cam, c, r);
    ts.push_back(tsk);
  }
  printf("\n");
}

void save_results(const image_task& img_tsk, const unsigned char * buffer,
                  const vector<result*>& rs)
{
  if (img_tsk.outfd > 0) {
    if (!img_tsk.bmp_padding) {
      lo.log("streamming raw pixel");
      write(img_tsk.outfd, buffer, size(img_tsk.d) * 3);
    } else {
      lo.log("streamming bmp file");
      stream(img_tsk.outfd, img_tsk.d, buffer);
    }
    lo.log("end streamming");
  } else if (img_tsk.dd.m > 1 && img_tsk.dd.n > 1) {
    for (auto it : rs) {
      char name[64];
      sprintf(name, "%s.%dX%d.part.[%d-%d)X[%d-%d).bmp",
              img_tsk.outfile.c_str(),
              img_tsk.dd.m, img_tsk.dd.n,
              it->c.w.l, it->c.w.r, it->c.h.l, it->c.h.r);
      lo.log("saving as " + string(name));
      save(name, from_clip(it->c), it->p);
    }
  } else {
    lo.log("saving as " + img_tsk.outfile);
    save(img_tsk.outfile.c_str(), img_tsk.d, buffer);
  }
}

void run(const image_task& img_tsk)
{
  if (img_tsk.t) return;
  engine e(img_tsk.dep, img_tsk.d);
  if (img_tsk.single) {
    auto g = e.rasterize(img_tsk.w, img_tsk.lights, img_tsk.cam,
                         img_tsk.i, img_tsk.j);
    auto p = rgb(g);
    printf("pix[%d, %d] = (%f, %f, %f) # %02x %02x %02x | %d %d %d\n",
           img_tsk.j, img_tsk.i, expand_c(g), expand_c(p), expand_c(p));
    return ;
  }

  auto sch = scheduler{img_tsk.d};
  auto a = (img_tsk.dd.m > 1 || img_tsk.dd.n > 1) ?
    sch.divide(img_tsk.dd) : sch.divide();

  vector<result*> rs;
  vector<task*> ts;
  unsigned char * buffer = img_tsk.buffer ? img_tsk.buffer : g_buffer;
  create_render_tasks(img_tsk, e, a, buffer, ts, rs);

  lo.log("begin rendering ...");
  run_tasks(ts, img_tsk.use_thread);
  lo.log("end rendering ...");
  save_results(img_tsk, buffer, rs);
  lo.log("done");
}

int app(int argc, char* argv[], const atlas& worlds, world_gen def)
{
  image_task img_tsk;
  if (not parse(argc, argv, img_tsk, worlds, def)) {
    usage(argv[0], worlds);
    return 0;
  }
  show_image_task(img_tsk);
  run(img_tsk);
  return 0;
}

int app(int argc, char* argv[]) { return app(argc, argv, atlas()); }
