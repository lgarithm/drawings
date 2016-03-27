#ifndef RAY_H
#define RAY_H

#include "bmp.h"
#include "color.h"
#include "display.h"
#include "guard.h"  // For transitive closure
#include "model.h"
#include "view.h"
#include "profile.h"  // For transitive closure

struct interval{ double lo, hi; };
struct viewport{ interval xr, yr; };
struct surface{ t_vector3 n; material m; };

struct shader
{
  const color bgc;
  const color def;
  shader(const color&, const color&);
  color operator()(const surface&, const vector3&,
                   const world&, const env&, int) const;
};

struct engine
{
  const int dep;
  display d;

  engine(int dep=2, const display=XGA);
  color rasterize(const world&, const env&, const camera&, int, int) const;
  void render(const world&, const env&, const camera&, unsigned char*) const;
  void render(const world&, const env&, const camera&, const clip&,
              unsigned char*) const;
};

color rasterize(const world&, const env&, const camera&, const display&,
                const viewport&, int, int, int dep);

#endif  // RAY_H
