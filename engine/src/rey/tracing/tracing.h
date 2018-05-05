#pragma once

#include <rey/model/model.h>
#include <rey/model/view.h>
#include <rey/optics/color.h>
#include <rey/tracing/display.h>

struct interval {
    double lo, hi;
};

struct viewport {
    interval xr, yr;
};

struct engine {
    const int dep;
    const display d;

    engine(int dep = 2, const display = XGA);
    color rasterize(const world &, const env &, const camera &,  //
                    int /* i */, int /* j */) const;
    void render(const world &, const env &, const camera &,
                unsigned char *) const;
    void render(const world &, const env &, const camera &, const clip &,
                unsigned char *) const;
};

color rasterize(const world &, const env &, const camera &, const display &,
                const viewport &, int /* i */, int /* j */, int /* dep */);
