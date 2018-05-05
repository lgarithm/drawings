#pragma once


#include <rey/optics/color.h>

struct material {
    color diffuse;
    color specular;
    unsigned char roughness;
    colorT reflection;

    material();

    // TODO
    // static const material
};


