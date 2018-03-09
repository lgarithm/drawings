#include "parallel.h"

#include <vector>
#if HAS_STD_THREAD
#include <atomic>
#include <mutex>
#include <thread>
#endif

#include "logger.h"

using std::vector;
#if HAS_STD_THREAD
using std::atomic;
using std::lock_guard;
using std::mutex;
using std::thread;
mutex wrt;
#endif

namespace
{
clogger lo;
} // namespace

task::task(const engine &e, const world &w, const env &l, const camera &cam,
           const clip &c, result *r)
    : id(++Id), e(e), w(w), l(l), cam(cam), c(c), r(r)
{
}

void task::operator()()
{
    e.render(w, l, cam, c, r->p);
    r->c = c;
}

int task::Id = 0;

void show_finished(int id)
{
    printf("\r%s\r", "                                       ");
    {
        with_c _(1, 42);
        printf("finished rendering task #[%d]", id);
    }
    fflush(stdout);
}

#if HAS_STD_THREAD
void run_in_threads(vector<task *> &tasks, int m)
{
    auto n = tasks.size();
    atomic<int> idx(0);
    vector<thread *> ts(m);
    for (int i = 0; i < m; ++i) {
        ts[i] = new thread([&]() {
            for (;;) {
                auto i = idx++;
                if (i < n) {
                    (*tasks[i])();
                    {
                        lock_guard<mutex> lck(wrt);
                        show_finished(tasks[i]->id);
                    }
                } else {
                    break;
                }
            }
        });
    }
    for (auto &it : ts) {
        it->join();
    }
    printf("\n");
}
#endif

void run_tasks(vector<task *> &tasks, bool use_thread)
{
#if HAS_STD_THREAD
    auto m = thread::hardware_concurrency();
    {
        with_c _(0, 45);
        printf("hardware_concurrency: %u", m);
    }
    printf("\n");
    if (use_thread) {
        run_in_threads(tasks, m);
        return;
    }
#endif
    for (auto tsk : tasks) {
        (*tsk)();
        show_finished(tsk->id);
    }
    printf("\n");
}
