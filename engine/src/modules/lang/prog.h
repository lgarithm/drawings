#pragma once


#include <string>

#include "constants.h" // for transitive closure
#include "material.h"
#include "maybe.h"
#include "model-builtin.h"
#include "model.h"

maybe<camera> p_camera(const std::string &);
maybe<material> p_material(const std::string &);
object *p_model(const std::string &);


