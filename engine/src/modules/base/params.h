#ifndef PARAMS_H
#define PARAMS_H

#include <string>
#include <vector>

#include "display.h"
#include "model.h"
#include "primitives.h"  // For traisitive closure
#include "ray.h"
#include "task.h"
#include "view.h"

static const int max_width = 4096;
static const int max_height = 4096;
static const int max_dep = 6;

bool parse(int argc, const char * const argv[], image_task&);
bool parse(int argc, const char * const argv[], image_task&,
           const atlas&, world_gen);
void usage(const char * name, const atlas&);

#endif  // PARAMS_H
