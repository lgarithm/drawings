#ifndef RAY_H
#define RAY_H

#include "bmp.h"
#include "color.h"
#include "model.h"

struct display{ unsigned short width, height; };
struct interval{ double lo, hi; };
struct viewport{ interval xr, yr; };
struct RGB{ unsigned char r, g, b; };

struct shader
{
  const color bgc;
  const color def;
  shader(const color&, const color&);
  color operator()(const intersection&, const scene&, int) const;
};

struct engine
{
  const int dep;
  engine(int dep=2);
  void render(const scene& s, const camera&, const viewport&, const display&,
              unsigned char*) const;
};

color rasterize(const scene&, const camera&,
                const viewport&, const display&,
                int, int, int dep);

#endif  // RAY_H
