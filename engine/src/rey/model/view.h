#pragma once
#include <rey/linear/linear.hpp>

struct camera {
    oframe of;
    scalar_t near;
    scalar_t aov;
    // TODO: scalarT far;
    // TODO: scalarT aspect = 1;

    camera();
    camera(const oframe &);
};

camera top(scalar_t = 10);
camera bottom(scalar_t = 10);
camera front(scalar_t = 10);
camera back(scalar_t = 10);
camera left(scalar_t = 10);
camera right(scalar_t = 10);
