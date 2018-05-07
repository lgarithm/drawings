#pragma once

#include <rey/model/model.h>
#include <rey/model/view.h>
#include <rey/optics/color.h>
#include <rey/tracing/display.h>
#include <rey/tracing/scene.hpp>
#include <rey/tracing/view.hpp>

struct engine {
    const int dep;
    const display d;

    engine(int dep = 2, const display = XGA);
    color rasterize(const scene_t &, int /* i */, int /* j */) const;
    void render(const scene_t &, unsigned char *) const;
    void render(const scene_t &, const clip &, unsigned char *) const;
};

extern color rasterize(const scene_t &, const display &, const viewport &,
                       int /* i */, int /* j */, int /* dep */);
