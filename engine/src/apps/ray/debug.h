#ifndef DEBUG_H
#define DEBUG_H

#include <cstdio>

#include "model.h"

/*
template <typename T>
void pp(const T& p) { printf("(%f, %f, %f)", p.x, p.y, p.z); }
*/

void pp(const point3& p);

void info(const camera& cam);

#endif  // DEBUG_H
