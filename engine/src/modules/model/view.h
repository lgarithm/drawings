#pragma once


#include "affine.h"

struct camera {
    oframe of;
    scalarT near;
    scalarT aov;
    // TODO: scalarT far;
    // TODO: scalarT aspect = 1;

    camera();
    camera(const oframe &);
};

camera top(scalarT = 10);
camera bottom(scalarT = 10);
camera front(scalarT = 10);
camera back(scalarT = 10);
camera left(scalarT = 10);
camera right(scalarT = 10);


