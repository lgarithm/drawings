#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>

#include "model.h"
#include "params.h"

void pp(const point3& p);
void info(const camera& cam);
void show_config(const config& cfg);

#endif  // DEBUG_H
