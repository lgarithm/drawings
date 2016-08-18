#ifndef POINT_IMPL_TPL_H
#define POINT_IMPL_TPL_H

template <typename T> struct point2_t {
    T x, y;
};
template <typename T> struct point3_t {
    T x, y, z;
};

template <typename P> P operator-(const P &p) { return P{-p.x, -p.y, -p.x}; }

template <typename P> P operator+(const P &p, const P &q)
{
    return P{p.x + q.x, p.y + q.y, p.z + q.z};
}

template <typename P> P operator-(const P &p, const P &q)
{
    return P{p.x - q.x, p.y - q.y, p.z - q.z};
}

template <typename T> T det(T a, T b, T c, T d) { return a * d - b * c; }

template <typename P> P cross(const P &p, const P &q)
{
    return P{det(p.y, p.z, q.y, q.z), det(p.z, p.x, q.z, q.x),
             det(p.x, p.y, q.x, q.y)};
}

template <typename P> bool operator==(const P &p, const P &q)
{
    return p.x == q.x && p.y == q.y && p.z == q.z;
};

template <typename T> point3_t<T> operator*(T r, const point3_t<T> &p)
{
    return point3_t<T>{r * p.x, r * p.y, r * p.z};
};

template <typename T> T dot(const point3_t<T> &p, const point3_t<T> &q)
{
    return p.x * q.x + p.y * q.y + p.z * q.z;
};

template <typename T>
point3_t<T> reflect(const point3_t<T> &n, const point3_t<T> &d)
{
    return d - T(2) * dot(n, d) * n;
}

using scalarT = double;
using point2 = point2_t<scalarT>;
using point3 = point3_t<scalarT>;
using vector2 = point2;
using vector3 = point3;

#endif // POINT_IMPL_TPL_H
