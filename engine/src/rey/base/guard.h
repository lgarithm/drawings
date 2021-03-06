#pragma once

#define USE_GUARD

#include <string>

#include <rey/base/config.h>
#include <rey/linear/linear.hpp>

void assert_unit(const vector3 &, const std::string, const std::string);
void assert_unit(const vector3 &, const std::string = "");
void assert_zero(scalarT, const std::string = "");
void assert_non_negative_zero(scalarT, const std::string = "");
