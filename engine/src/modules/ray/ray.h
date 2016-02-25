#ifndef RAY_H
#define RAY_H

#include "bmp.h"
#include "model.h"

struct display{ unsigned short width, height; };
struct interval{ double lo, hi; };
struct viewport{ interval xr, yr; };
struct RGB{ unsigned char r, g, b; };

color rasterize(const scene& s, const viewport& v, const display& d, int i, int j);
void render(const scene& s, const viewport& v, const display& d, unsigned char* buffer);
color trace(const ray& r, const scene& s, int dep);

const auto black = color{0, 0, 0};
const auto red = color{1, 0, 0};
const auto green = color{0, 1, 0};
const auto blue = color{0, 0, 1};
const auto white = red + green + blue;
const auto grey = .5 * (black + white);
const auto background = black;
const auto defaultColor = black;

#endif  // RAY_H
