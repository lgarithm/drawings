#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>

#include "model.h"
#include "params.h"

#define expand_c(c) c.r, c.g, c.b
#define expand_v(v) v.x, v.y, v.z

void pp(const point3& p);
void info(const camera& cam);
void show_config(const config& cfg);

#endif  // DEBUG_H
