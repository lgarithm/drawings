#include <apps/bb8/bb8_model.h>

#include <cmath>

#include <algorithm>

#include <rey/rey>

using std::max;
using std::min;

bb8_head::bb8_head(double size, const oframe &of)
    : bound(sphere(size, of.origin)), of(of)
{
}

bool bb8_head::in(const point3 &p) const { return local(of, p)._val[2] > 0; }

material bb8_head::mt(const point3 &p) const
{
    material m;
    auto q = norm(local(of, p) - origin);
    auto g = asin(q._val[2]) * radian;
    if (g > 10) {
        if (g > 50 && g < 60) {
            m.diffuse = orange;
        } else {
            m.diffuse = white;
        }
    } else {
        m.diffuse = grey;
    }
    return m;
}

bb8_body::bb8_body(double size, const oframe &of)
    : sphere(size, of.origin), of(of)
{
}

material bb8_body::mt(const point3 &p) const
{
    material m;
    const auto q = norm(local(of, p) - origin);
    const auto r = pos3(fabs(q._val[0]), fabs(q._val[1]), fabs(q._val[2]));
    auto th =
        acos(max({dot(r, x_axis), dot(r, y_axis), dot(r, z_axis)})) * radian;

    if (th < 30) {
        if (th < 20) {
            m.diffuse = grey;
        } else {
            m.diffuse = orange;
        }
    } else {
        /*
          static const auto eps = 5e-3;
          if (fabs(q.x) <  eps|| fabs(q.y) < eps || fabs(q.z) < eps) {
          s.m.diffuse = grey;
          }//*/
    }
    m.reflection = .2;
    return m;
}

bb8::bb8(double size, const oframe &of)
    : head(.5 * size, of + size * z_axis), body(size, of)
{
}

std::optional<intersection> bb8::intersect(const ray &r) const
{
    return nearest<std::initializer_list<const object *>>({&body, &head}, r);
}
