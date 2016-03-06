#include "guard.h"

#include <cassert>
#include <cmath>
#include <cstdio>

#include <string>

using std::string;

#ifdef USE_GUARD

void assert_unit(const vector3& v, const string s)
{
  auto d = fabs(len(v) - 1);
  bool p = d < 1e-9;
  if (not p) {
    fprintf(stderr, "failed to %s, diff %f, %s\n", __func__, d, s.c_str());
    assert(false);
  }
}

#else

void assert_unit(const vector3& v, const string s) {}

#endif  // #ifdef USE_GUARD
