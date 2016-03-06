#include "app.h"

#include <cstdio>

#include <algorithm>
#include <memory>
#include <vector>

#if HAS_STD_THREAD
  #include <thread>
#endif

#include "bmp.h"
#include "debug.h"
#include "display.h"
#include "logger.h"
#include "model.h"
#include "params.h"
#include "ray.h"

using std::vector;
using std::string;

#if HAS_STD_THREAD
  using std::thread;
#endif

namespace
{
  clogger lo;
  static const int buffer_size = 3 * max_width * max_height;
  unsigned char buffer[buffer_size];
  unsigned char* buffers[64];
}

void save(const char * name, const display& d, const unsigned char * buffer)
{
  bmp_head head;
  head.init(d.width, d.height);
  write_bmp_file(head, buffer, name);
}

struct result
{
  clip c;
  unsigned char *p;
};

struct task
{
  static int Id;

  const int id;
  const engine e;
  const world& w;
  const env l;
  const camera cam;
  const clip c;
  unsigned char *p;

  result* r;

  task(const engine& e, const world& w, const env& l,
       const camera& cam, const clip& c, unsigned char *p, result* r) :
    id(++Id), e(e), w(w), l(l), cam(cam), c(c), p(p), r(r) {}

  void operator()()
  {
    char msg[64];
    sprintf(msg, "begin rendering task #%d", id);
    lo.log(msg);
    e.render(w, l, cam, c, p);
    r->c = c;
    r->p = p;
    sprintf(msg, "finished rendering task #%d", id);
    lo.log(msg);
  }
};

int task::Id = 0;

void run(const config& cfg, const scene& s)
{
  if (cfg.t) return;

  engine e(cfg.dep, cfg.d);
  auto sch = scheduler{cfg.d};
  auto a = sch.divide();
  if (cfg.dd.m > 1 || cfg.dd.n > 1) a = sch.divide(cfg.dd.m, cfg.dd.n);
  size_t n = a.size();

  lo.log("begin rendering ...");

  #if HAS_STD_THREAD
    vector<thread*> ts;
  #endif
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
    if (cfg.use_thread) {
      #if HAS_STD_THREAD
        auto th = new thread(*tsk);
        ts.push_back(th);
      #else
        (*tsk)();
      #endif
    } else {
      (*tsk)();
    }
  }
  #if HAS_STD_THREAD
    for (auto& it : ts) { it->join(); }
  #endif

  if (cfg.dd.m > 1 && cfg.dd.n > 1) {
    for (auto it : rs) {
      char name[64];
      sprintf(name, "%s.part.[%d-%d)X[%d-%d).bmp", cfg.outfile.c_str(),
        it->c.w.l, it->c.w.r, it->c.h.l, it->c.h.r);
      lo.log("saving as " + string(name));
      save(name, from_clip(it->c), it->p);
    }
  } else {
    lo.log("saving as " + cfg.outfile);
    save(cfg.outfile.c_str(), cfg.d, buffer);
  }
  lo.log("done");
}
