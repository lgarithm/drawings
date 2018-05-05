#pragma once


#include <vector>

#include <rey/base/config.h> // for HAS_STD_THREAD
#include <rey/base/debug.h>
#include <rey/ray/display.h>
#include <rey/model/model.h>
#include <rey/ray/ray.h>
#include <rey/model/view.h>

struct result {
    clip c;
    unsigned char *p;
};

struct task {
    static int Id;

    const int id;
    const engine e;
    const world &w;
    const env l;
    const camera cam;
    const clip c;
    result *r;

    task(const engine &, const world &, const env &, const camera &,
         const clip &, result *);
    void operator()();
};

void run_tasks(std::vector<task *> &, bool = false);


