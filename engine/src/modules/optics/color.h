#pragma once

#include "config.h"

typedef COLOR_T colorT;

#ifdef USE_TEMPLATE

template <typename T> struct colorT {
    T r, g, b;
};

template <typename T> colorT<T> operator*(T b, const colorT<T> &c)
{
    return colorT<T>{b * c.r, b * c.g, b * c.b};
}

template <typename T>
colorT<T> operator+(const colorT<T> &p, const colorT<T> &q)
{
    return colorT<T>{p.r + q.r, p.g + q.g, p.b + q.b};
}

template <typename T>
colorT<T> operator*(const colorT<T> &p, const colorT<T> &q)
{
    return colorT<T>{p.r * q.r, p.g * q.g, p.b * q.b};
}

using color = colorT<colorT>;

#else

#include "tuple.h"

DEFINE_TUPLE_3(color, colorT, r, g, b);

DECLARE_TUPLE_3_SCALE(colorT, color, r, g, b);
DECLARE_TUPLE_3_ADD(color, r, g, b);
DECLARE_TUPLE_3_MUL(color, r, g, b);
DECLARE_TUPLE_3_INC(color, r, g, b);
DECLARE_TUPLE_3_EQU(color, r, g, b);

#endif // USE_TEMPLATE

struct RGB {
    unsigned char r, g, b;
};
RGB rgb(const color &);

static const auto black = color{0, 0, 0};
static const auto red = color{1, 0, 0};
static const auto green = color{0, 1, 0};
static const auto blue = color{0, 0, 1};
static const auto yellow = red + green;
static const auto orange = red + .5 * green;
static const auto white = red + green + blue;
static const auto grey = .5 * (black + white);
