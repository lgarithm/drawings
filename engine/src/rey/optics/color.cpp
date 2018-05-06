#include <rey/optics/color.h>

RGB rgb(const color &c)
{
    static const auto f = [](colorT s) {
        return (unsigned char)(255 * (s > 1 ? 1 : s));
    };
    return RGB{f(c._val[0]), f(c._val[1]), f(c._val[2])};
}
