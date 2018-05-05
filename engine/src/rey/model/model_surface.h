#pragma once


#include <rey/arith/arith.h>
#include <rey/base/maybe.h>
#include <rey/model/model.h>
#include <rey/linear/point.h>

struct algebraic_surface : simple_object {
    oframe of;

    algebraic_surface();
    algebraic_surface(const oframe &);

    vector3 at(const point3 &) const override;
    virtual vector3 n_at(const point3 &) const = 0;
};

struct quadratic_surface : algebraic_surface {
    maybe<scalarT> meet(const ray &) const override;

    quadratic_surface(const oframe &_ = oframe());
    virtual quad_eq equation(const ray &) const = 0;
};

struct ellipsoid : quadratic_surface {
    scalarT a, b, c;

    ellipsoid(scalarT, scalarT, scalarT);
    quad_eq equation(const ray &) const override;
    vector3 n_at(const point3 &) const override;
};

struct cylinder_surface : quadratic_surface {
    scalarT R;

    cylinder_surface(scalarT, const oframe &_ = oframe());
    quad_eq equation(const ray &) const override;
    vector3 n_at(const point3 &) const override;
};

struct cone_surface : quadratic_surface {
    scalarT k;

    cone_surface(scalarT);
    quad_eq equation(const ray &) const override;
    vector3 n_at(const point3 &) const override;
};

struct bound_cylinder_surface : bound<cylinder_surface> {
    scalarT h;
    bound_cylinder_surface(scalarT, scalarT, const oframe &_ = oframe());
    bool in(const point3 &)const override;
};


