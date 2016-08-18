#ifndef R2D2_MODEL_H
#define R2D2_MODEL_H

#include "rey.h"

struct r2d2_head : sphere {
    oframe of;

    r2d2_head(scalarT, const oframe &);
    maybe<scalarT> meet(const ray &) const override;
    material mt(const point3 &) const override;
};

struct r2d2_body : bound_cylinder_surface {
    r2d2_body(scalarT, scalarT, const oframe &);
    material mt(const point3 &) const override;
};

struct r2d2 : object {
    r2d2_head head;
    r2d2_body body;
    disc bottom;

    r2d2(scalarT r, scalarT h, const oframe &_ = oframe());
    maybe<intersection> intersect(const ray &r) const override;
};

#endif // R2D2_MODEL_H
