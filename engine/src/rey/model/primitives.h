#pragma once


#include <rey/linear/affine.h>
#include <rey/base/guard.h> // for transitive closure
#include <rey/base/maybe.h>
#include <rey/model/model.h>
#include <rey/linear/point.h>

struct plane : simple_object {
    t_vector3 n;

    plane(const t_vector3 &);

    std::optional<scalarT> meet(const ray &) const override;
    vector3 at(const point3 &) const override;
};

struct Floor : plane {
    Floor();
};

struct disc : bound<plane> {
    scalarT R;

    disc(scalarT, const t_vector3 &);

    bool in(const point3 &)const override;
};

struct triangle : bound<plane> {
    const point3 a, b, c;

    triangle(const point3 &, const point3 &, const point3 &);

    bool in(const point3 &)const override;
};

struct quad : bound<plane> {
    oframe of;
    scalarT half_w, half_h;

    quad(const oframe &, scalarT, scalarT);

    bool in(const point3 &)const override;
};

struct Chessboard : plane {
    double grid_size;
    Chessboard(double = 1);
    material mt(const point3 &) const override;
};

struct sphere : simple_object {
    double size;
    point3 pos;

    sphere(double, const point3 &);

    std::optional<scalarT> meet(const ray &) const override;
    vector3 at(const point3 &) const override;
};

struct tetrahedron : object {
    triangle f[4];
    object *subs[4];
    tetrahedron(const point3 &, const point3 &, const point3 &, const point3 &);
    std::optional<intersection> intersect(const ray &) const override;
};

std::optional<scalarT> r_dis(const t_vector3 &, const ray &);


