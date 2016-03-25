#ifndef PROG_H
#define PROG_H

#include <string>

#include "material.h"
#include "maybe.h"
#include "model.h"
#include "model-builtin.h"

object* p_model(const std::string&);
maybe<material> p_material(const std::string&);

#endif  // PROG_H
