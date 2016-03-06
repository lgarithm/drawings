#ifndef EXAMPLE_H
#define EXAMPLE_H

#include <map>
#include <string>

#include "bb8_model.h"
#include "model.h"

std::map<std::string, world_gen> examples();

world* example_1();
world* example_2();
world* test_room();

#endif  // EXAMPLE_H
