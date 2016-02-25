#include "color.h"

#ifdef USE_TEMPLATE

#else

DEFINE_TUPLE_3_SCALE(double, color, r, g, b);
DEFINE_TUPLE_3_PLUS(color, r, g, b);
DEFINE_TUPLE_3_TIMES(color, r, g, b);

#endif  // USE_TEMPLATE
