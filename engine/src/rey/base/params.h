#pragma once

#include <string>
#include <vector>

#include <rey/base/task.h>
#include <rey/lang/prog.h>
#include <rey/model/model.h>
#include <rey/model/primitives.h>
#include <rey/model/view.h>
#include <rey/tracing/display.h>
#include <rey/tracing/tracing.h>

static const int max_width = 4096;
static const int max_height = 4096;
static const int max_dep = 6;

bool parse(int argc, const char *const argv[], image_task &);
bool parse(int argc, const char *const argv[], image_task &, const atlas &,
           world_gen);
void usage(const char *name, const atlas &);
