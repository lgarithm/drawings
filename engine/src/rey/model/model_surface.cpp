#include "model_surface.h"

#include <cassert>

#include <string>

#include <rey/arith/arith.h>
#include <rey/base/debug.h>
#include <rey/base/guard.h>

algebraic_surface::algebraic_surface() {}

algebraic_surface::algebraic_surface(const oframe &of) : of(of) {}

vector3 algebraic_surface::at(const point3 &p) const
{
    auto n = n_at(local(of, p));
    assert_unit(n, __FILE__, __func__);
    return n;
}

quadratic_surface::quadratic_surface(const oframe &of) : algebraic_surface(of)
{
}

std::optional<scalarT> quadratic_surface::meet(const ray &r) const
{
    const auto r_ = local(of, r);
    const auto e = equation(r_);
    if (eval(e, 0) < 0)
        return nothing<scalarT>();
    numericT t, t_;
    if (not min_positive_root(e, t))
        return nothing<scalarT>();
    assert(fabs(eval(e, t)) < 1e-1);
    return just(t);
}

ellipsoid::ellipsoid(scalarT a, scalarT b, scalarT c) : a(a), b(b), c(c) {}

quad_eq ellipsoid::equation(const ray &r) const
{
    return (quad_eq{0, 0, -1} + sqr(1. / a * linear_eq{r.v.x, r.o.x}) +
            sqr(1. / b * linear_eq{r.v.y, r.o.y}) +
            sqr(1. / c * linear_eq{r.v.z, r.o.z}));
}

vector3 ellipsoid::n_at(const point3 &p) const
{
    return norm(p / pos3(a * a, b * b, c * c) - origin);
}

cylinder_surface::cylinder_surface(scalarT R, const oframe &of)
    : quadratic_surface(of), R(R)
{
}

quad_eq cylinder_surface::equation(const ray &r) const
{
    return (quad_eq{0, 0, -R * R} + sqr(linear_eq{r.v.x, r.o.x}) +
            sqr(linear_eq{r.v.y, r.o.y}));
}

vector3 cylinder_surface::n_at(const point3 &p) const
{
    return norm(vec3(p.x, p.y, 0));
}

cone_surface::cone_surface(scalarT k) : k(k) {}

quad_eq cone_surface::equation(const ray &r) const
{
    return (sqr(linear_eq{r.v.x, r.o.x}) + sqr(linear_eq{r.v.y, r.o.y}) -
            sqr(k * linear_eq{r.v.z, r.o.z}));
}

vector3 cone_surface::n_at(const point3 &p) const
{
    //  assert(p.z > 0);
    return norm(vec3(p.x, p.y, -k * k * p.z));
}

bound_cylinder_surface::bound_cylinder_surface(scalarT r, scalarT h,
                                               const oframe &of)
    : bound(cylinder_surface(r, of)), h(h)
{
}

bool bound_cylinder_surface::in(const point3 &p) const
{
    auto zz = local(of, p).z * 2;
    return -h < zz && zz < h;
}
