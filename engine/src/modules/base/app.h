#ifndef APP_H
#define APP_H

#include <map>
#include <string>

#include "model.h"

int app(int, char* argv[]);
int app(int, char* argv[], std::map<std::string, world_gen>, world_gen=nullptr);

#endif  // APP_H
