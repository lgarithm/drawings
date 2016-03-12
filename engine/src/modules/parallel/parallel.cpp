#include "parallel.h"

#include <vector>
#if HAS_STD_THREAD
#include <thread>
#endif

#include "logger.h"

using std::vector;
#if HAS_STD_THREAD
using std::thread;
#endif

namespace
{
  clogger lo;
}  // namespace

task::task(const engine& e, const world& w, const env& l,
           const camera& cam, const clip& c, unsigned char *p, result* r) :
  id(++Id), e(e), w(w), l(l), cam(cam), c(c), p(p), r(r) {}

void task::operator()()
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

int task::Id = 0;

void run_tasks(vector<task*>& tasks, bool use_thread)
{
  auto m = thread::hardware_concurrency();
  printf("hardware_concurrency: %u\n", m);
#if HAS_STD_THREAD
  vector<thread*> ts;
#endif
  for (auto tsk : tasks) {
    if (use_thread) {
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
}
