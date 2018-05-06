#pragma once

#include <rey/base/config.h>
#include <rey/linear/linear.hpp>

using colorT = COLOR_T;

struct Optics;
using color = rey::linear::tuple::_tuple_t<colorT, 3, Optics>;

inline color operator+(const color &c, const color &d)
{
    return rey::linear::tuple::_tuple_add<Optics>(c, d);
}

inline void operator+=(color &c, const color &d)
{
    return rey::linear::tuple::_tuple_inc(c, d);
}

inline color operator*(const color &c, const color &d)
{
    return rey::linear::tuple::_tuple_mul<Optics>(c, d);
}

inline color operator*(colorT r, const color &c)
{
    return rey::linear::tuple::_tuple_scale(r, c);
}

struct RGB {
    unsigned char r, g, b;
};

RGB rgb(const color &);

static const auto black = color(0, 0, 0);
static const auto red = color(1, 0, 0);
static const auto green = color(0, 1, 0);
static const auto blue = color(0, 0, 1);
static const auto yellow = red + green;
static const auto orange = red + .5 * green;
static const auto white = red + green + blue;
static const auto grey = .5 * (black + white);
