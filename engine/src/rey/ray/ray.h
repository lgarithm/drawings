#pragma once


#include <rey/bmp/bmp.h>
#include <rey/optics/color.h>
#include <rey/ray/display.h>
#include <rey/base/guard.h>
#include <rey/model/model.h>
#include <rey/profile/profile.h> // For transitive closure
#include <rey/model/view.h>



struct interval {
    double lo, hi;
};
struct viewport {
    interval xr, yr;
};

struct engine {
    const int dep;
    display d;

    engine(int dep = 2, const display = XGA);
    color rasterize(const world &, const env &, const camera &, int, int) const;
    void render(const world &, const env &, const camera &,
                unsigned char *) const;
    void render(const world &, const env &, const camera &, const clip &,
                unsigned char *) const;
};

color rasterize(const world &, const env &, const camera &, const display &,
                const viewport &, int, int, int dep);


