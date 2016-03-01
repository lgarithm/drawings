#include "color.h"

#ifdef USE_TEMPLATE

#else

DEFINE_TUPLE_3_SCALE(double, color, r, g, b);
DEFINE_TUPLE_3_PLUS(color, r, g, b);
DEFINE_TUPLE_3_TIMES(color, r, g, b);

#endif  // USE_TEMPLATE

RGB rgb(const color& c)
{
  static const auto f = [](double s)
    { return (unsigned char) (255 * (s > 1 ? 1 : s)); };
  return RGB{f(c.r), f(c.g), f(c.b)};
}
