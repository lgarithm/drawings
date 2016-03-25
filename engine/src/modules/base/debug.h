#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>

#include "model.h"
#include "params.h"

#define expand_c(c) c.r, c.g, c.b
#define expand_v(v) v.x, v.y, v.z

template<typename T>
void pp(const T& p) { printf("(%f, %f, %f)", expand_v(p)); }

void info(const camera& cam);
void info(const world& w);
void show_image_task(const image_task& cfg);

#endif  // DEBUG_H
