#ifndef APP_H
#define APP_H

#include "logger.h"
#include "model.h"
#include "params.h"

int app(int argc, char* argv[]);
void run(const config&, const scene&);

#endif  // APP_H
