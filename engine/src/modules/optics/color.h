#ifndef COLOR_H
#define COLOR_H

#ifdef USE_TEMPLATE

template <typename T> struct colorT { T r, g, b; };

template <typename T> colorT<T> operator*(T b, const colorT<T>& c)
{ return colorT<T>{b * c.r, b * c.g, b * c.b}; }

template <typename T>
colorT<T> operator+(const colorT<T>& p, const colorT<T>& q)
{ return colorT<T>{p.r + q.r, p.g + q.g, p.b + q.b}; }

template <typename T>
colorT<T> operator*(const colorT<T>& p, const colorT<T>& q)
{ return colorT<T>{p.r * q.r, p.g * q.g, p.b * q.b}; }

using color = colorT<double>;

#else

#include "tuple.h"

DEFINE_TUPLE_3(color, double, r, g, b);

color operator*(double, const color&);
color operator+(const color&, const color&);
color operator*(const color&, const color&);

#endif  // USE_TEMPLATE

struct RGB{ unsigned char r, g, b; };
RGB rgb(const color&);

static const auto black = color{0, 0, 0};
static const auto red = color{1, 0, 0};
static const auto green = color{0, 1, 0};
static const auto blue = color{0, 0, 1};
static const auto yellow = red + green;
static const auto orange = red + .5 * green;
static const auto white = red + green + blue;
static const auto grey = .5 * (black + white);

#endif  // COLOR_H
