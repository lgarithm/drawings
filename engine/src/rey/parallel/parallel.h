#pragma once

#include <vector>

#include <rey/base/config.h>  // for HAS_STD_THREAD
#include <rey/base/debug.h>
#include <rey/model/model.h>
#include <rey/model/view.h>
#include <rey/tracing/display.h>
#include <rey/tracing/tracing.h>

struct result {
    clip c;
    unsigned char *p;
};

struct task {
    static int Id;

    const int id;
    const engine e;
    const scene_t &scene;
    const clip c;
    result *r;

    task(const engine &, const scene_t &, const clip &, result *);
    void operator()();
};

void run_tasks(std::vector<task *> &, bool = false);
