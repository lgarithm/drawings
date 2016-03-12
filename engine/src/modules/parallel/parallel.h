#ifndef PARALLEL_H
#define PARALLEL_H

#include <vector>

#include "config.h"  // for HAS_STD_THREAD
#include "debug.h"
#include "display.h"
#include "model.h"
#include "ray.h"

struct result { clip c; unsigned char *p; };

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
       const camera& cam, const clip& c, unsigned char *p, result* r);
  void operator()();
};

void run_tasks(std::vector<task*>& tasks, bool use_thread=false);

#endif  // PARALLEL_H
