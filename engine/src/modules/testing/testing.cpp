#include "testing.h"

#include <cstdio>

#include "logger.h"

namespace
{
const auto eps = 1e-6;
}

void assert_eq(double x, double y)
{
    double e = fabs(x - y);
    char msg[64];
    sprintf(msg, "asserting %f == %f, delta=%e", x, y, e);
    clogger lo;
    lo.log(msg);
    assert(e < eps);
}
