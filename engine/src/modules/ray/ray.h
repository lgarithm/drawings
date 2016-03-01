#ifndef RAY_H
#define RAY_H

#include "bmp.h"
#include "color.h"
#include "display.h"
#include "guard.h"  // For transitive closure
#include "model.h"

struct interval{ double lo, hi; };
struct viewport{ interval xr, yr; };

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
