// Basic linear Algebra for 1,2,3,4-d
#pragma once
#include <cassert>
#include <cmath>

#include <rey/linear/tuple-tpl.hpp>

template <typename T> bool zero(T x) { return std::fabs(x) < 1e-12; }

using scalar_t = double;

using point2 = rey::linear::affine::point_t<scalar_t, 2>;
using point3 = rey::linear::affine::point_t<scalar_t, 3>;
using vector2 = rey::linear::affine::vector_t<scalar_t, 2>;
using vector3 = rey::linear::affine::vector_t<scalar_t, 3>;

struct Simplex;
using simplex2 = rey::linear::tuple::_tuple_t<point3, 3, Simplex>;

using frame = rey::linear::affine::frame_t<scalar_t, 3>;
using oframe = rey::linear::affine::tangent_frame_t<scalar_t, 3>;
using t_vector3 = rey::linear::affine::tangent_vector_t<scalar_t, 3>;
using ray = t_vector3;

inline point2 pos2(scalar_t x, scalar_t y)
{
    return rey::linear::affine::pos<scalar_t>(x, y);
}

inline point3 pos3(scalar_t x, scalar_t y, scalar_t z)
{
    return rey::linear::affine::pos<scalar_t>(x, y, z);
}

inline vector3 dir3(scalar_t x, scalar_t y, scalar_t z)
{
    return rey::linear::affine::dir<scalar_t>(x, y, z);
}

#define vec3 dir3

static const auto origin = pos3(0, 0, 0);
static const auto x_axis = dir3(1, 0, 0);
static const auto y_axis = dir3(0, 1, 0);
static const auto z_axis = dir3(0, 0, 1);

// inline scalar_t dot(const vector3 &p, const vector3 &q)
// {
//     return rey::linear::affine::dot(p, q);
// }

template <typename T, uint8_t n, typename K1, typename K2>
inline scalar_t dot(const rey::linear::tuple::_tuple_t<T, n, K1> &p,
                    const rey::linear::tuple::_tuple_t<T, n, K2> &q)
{
    return rey::linear::tuple::_tuple_dot(p, q);
}

inline scalar_t len(const vector3 &p) { return rey::linear::affine::len(p); }

template <typename T> T det(T A, T B, T C, T D) { return A * D - B * C; }

inline scalar_t det(const vector2 &p, const vector2 &q)
{
    return det(p._val[0], p._val[1], q._val[0], q._val[1]);
}

inline vector3 cross(const vector3 &p, const vector3 &q)
{
    return dir3(det(p._val[1], p._val[2], q._val[1], q._val[2]),
                det(p._val[2], p._val[0], q._val[2], q._val[0]),
                det(p._val[0], p._val[1], q._val[0], q._val[1]));
}

inline vector3 norm(const vector3 &p)
{
    const scalar_t l = len(p);
    assert(l != 0);
    return l == 0 ? p : (1.0 / l) * p;
}

inline vector3 norm(const vector3 &a, const vector3 &b, const vector3 &c)
{
    return norm(cross(b - a, c - a));
}

inline point3 local(const frame &f, const point3 &p)
{
    return point3(dot(p, f.axises[0]), dot(p, f.axises[1]),
                  dot(p, f.axises[2]));
}

inline point3 global(const frame &f, const point3 &p)
{
    return origin + p._val[0] * f.axises[0] + p._val[1] * f.axises[1] +
           p._val[2] * f.axises[2];
}

inline point3 local(const oframe &of, const point3 &p)
{
    return local(of.frame, origin + (p - of.origin));
}

inline point3 global(const oframe &of, const point3 &p)
{
    return of.origin + (global(of.frame, p) - origin);
}

inline t_vector3 local(const oframe &of, const t_vector3 &t)
{
    return t_vector3(local(of, t.origin),
                     local(of.frame, origin + t.direction) - origin);
}

inline t_vector3 global(const oframe &of, const t_vector3 &t)
{
    return t_vector3(global(of, t.origin),
                     global(of.frame, origin + t.direction) - origin);
}

inline oframe observer(const point3 &pos, const point3 &focus,
                       const vector3 &up)
{
    auto Y = norm(focus - pos);
    auto X = norm(cross(Y, up));
    auto Z = cross(X, Y);
    return oframe(pos, frame(X, Y, Z));
}

inline point3 operator+(const t_vector3 &tv, scalar_t d)
{
    return tv.origin + d * tv.direction;
}

inline t_vector3 operator+(const t_vector3 &tv, const vector3 &d)
{
    return t_vector3(tv.origin + d, tv.direction);
}

inline vector3 reflect(const vector3 &n, const vector3 &d)
{
    return d - 2.0 * dot(n, d) * n;
}

inline scalar_t area2(const point3 &a, const point3 &b, const point3 &c)
{
    return len(cross(b - a, b - c));
}

inline bool in(const point3 &o, const simplex2 &s)
{
    return zero(area2(s._val[0], s._val[1], s._val[2]) -
                area2(o, s._val[0], s._val[1]) -
                area2(o, s._val[1], s._val[2]) -
                area2(o, s._val[2], s._val[0]));
}

inline oframe operator+(const oframe &of, const vector3 &v)
{
    return oframe(of.origin + v, of.frame);
}
