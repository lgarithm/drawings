#include "guard.h"

#include <cassert>
#include <cmath>

void assert_unit(const vector3& v) { assert(fabs(len(v) - 1) < 1e-9); }
