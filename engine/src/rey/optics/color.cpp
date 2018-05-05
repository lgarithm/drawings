#include <rey/optics/color.h>

#ifdef USE_TEMPLATE

#else

DEFINE_TUPLE_3_SCALE(colorT, color, r, g, b);
DEFINE_TUPLE_3_ADD(color, r, g, b);
DEFINE_TUPLE_3_MUL(color, r, g, b);
DEFINE_TUPLE_3_INC(color, r, g, b);
DEFINE_TUPLE_3_EQU(color, r, g, b);

#endif

RGB rgb(const color &c)
{
    static const auto f = [](colorT s) {
        return (unsigned char)(255 * (s > 1 ? 1 : s));
    };
    return RGB{f(c.r), f(c.g), f(c.b)};
}
