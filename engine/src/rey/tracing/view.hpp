#pragma once

struct interval {
    double lo, hi;
};

struct viewport {
    interval xr, yr;
};

struct view_t {
    const viewport vp;

    //
};
