#include "parallel.h"

#include <vector>
#if HAS_STD_THREAD
#include <mutex>
#include <thread>
#endif

#include "logger.h"

using std::vector;
#if HAS_STD_THREAD
using std::thread;
using std::mutex;
using std::lock_guard;
mutex wrt;
#endif

namespace
{
  clogger lo;
}  // namespace

task::task(const engine& e, const world& w, const env& l,
           const camera& cam, const clip& c, result* r) :
  id(++Id), e(e), w(w), l(l), cam(cam), c(c), r(r) {}

void task::operator()()
{
  e.render(w, l, cam, c, r->p);
  r->c = c;
  {
#if HAS_STD_THREAD
    lock_guard<mutex> lck(wrt);
#endif
    printf("\r%s\r", "                                       ");
    {
      with_c _(1, 42);
      printf("finished rendering task #[%d]", id);
    }
    fflush(stdout);
  }
}

int task::Id = 0;

void run_tasks(vector<task*>& tasks, bool use_thread)
{
#if HAS_STD_THREAD
  auto m = thread::hardware_concurrency();
  {
    with_c _(1, 44);
    printf("hardware_concurrency: %u", m);
  }
  printf("\n");
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
  printf("\n");
}
