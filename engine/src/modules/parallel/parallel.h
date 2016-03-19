#ifndef PARALLEL_H
#define PARALLEL_H

#include <vector>

#include "config.h"  // for HAS_STD_THREAD
#include "debug.h"
#include "display.h"
#include "model.h"
#include "view.h"
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
  result* r;

  task(const engine&, const world&, const env&,
       const camera&, const clip&, result*);
  void operator()();
};

void run_tasks(std::vector<task*>&, bool=false);

#endif  // PARALLEL_H
