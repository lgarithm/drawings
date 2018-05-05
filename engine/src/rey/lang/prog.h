#pragma once


#include <string>

#include <rey/lang/constants.h> // for transitive closure
#include <rey/optics/material.h>
#include <rey/base/maybe.h>
#include <rey/model/model-builtin.h>
#include <rey/model/model.h>

maybe<camera> p_camera(const std::string &);
maybe<material> p_material(const std::string &);
object *p_model(const std::string &);




