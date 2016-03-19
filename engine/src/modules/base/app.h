#ifndef APP_H
#define APP_H

#include <map>
#include <string>

#include "model.h"
#include "params.h"
#include "task.h"

int app(int, char* argv[]);
int app(int, char* argv[], const atlas&, world_gen=nullptr);
void run(const config& cfg);

#endif  // APP_H
