#include "r2d2_model.h"

#include <algorithm>

#include "rey.h"

using namespace std;

r2d2_head::r2d2_head(scalarT r, const oframe &of) : sphere(r, of.o), of(of) {}

maybe<scalarT> r2d2_head::meet(const ray &r) const
{
    const auto t = sphere::meet(r);
    const auto f = [&](scalarT d) {
        auto z = local(of, r + d).z;
        return z > 0 ? just(d) : nothing<scalarT>();
    };
    return inject(t, f);
}

material r2d2_head::mt(const point3 &p) const
{
    material m;
    auto q = norm(local(of, p) - origin);
    auto g = asin(q.z) * radian;
    if (g > 15) {
        if (g > 50 && g < 70) {
            m.diffuse = blue;
        } else {
            m.diffuse = white;
        }
    } else {
        m.diffuse = blue;
    }
    return m;
}

r2d2_body::r2d2_body(scalarT r, scalarT h, const oframe &of)
    : bound_cylinder_surface(r, h, of)
{
}

material r2d2_body::mt(const point3 &p) const
{
    material m;
    auto q = local(of, p);
    auto d1 = atan2(q.y, q.x) * radian;
    if (-2 < q.z && q.z < 1.5) {
        if (90 - 15 < d1 && d1 < 90 + 15) {
            m.diffuse = blue;
        }
    } else if ((1.8 < q.z && q.z < 2.4) || (2.6 < q.z && q.z < 3.2)) {
        if (90 - 30 < d1 && d1 < 90 + 30) {
            m.diffuse = blue;
        }
    }
    return m;
}

r2d2::r2d2(scalarT r, scalarT h, const oframe &of)
    : head(r, of + .5 * h * of.f.Z), body(r, h, of),
      bottom(r, t_vector3(of.o + -.5 * h * of.f.Z, -of.f.Z))
{
}

maybe<intersection> r2d2::intersect(const ray &r) const
{
    return min({body.intersect(r), head.intersect(r), bottom.intersect(r)});
}
