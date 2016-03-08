#ifndef BUILTIN_EXAMPLE_H
#define BUILTIN_EXAMPLE_H

#include <map>
#include <string>

#include "model.h"

std::map<std::string, world_gen> examples();
world* default_test_scene();

#endif  // BUILTIN_EXAMPLE_H
