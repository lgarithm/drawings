#pragma once
#include <array>
#include <cstdint>
#include <functional>

namespace rey::linear
{
namespace tuple
{
template <typename T, uint8_t n, typename K> struct _tuple_t {
    std::array<T, n> _val;

    _tuple_t() {}

    template <typename... Args>
    explicit _tuple_t(Args... x) : _val({static_cast<T>(x)...})
    {
        static_assert(sizeof...(Args) == n);
    }
};

// template <typename K, typename T, uint8_t n, typename K1, typename K2,
//           typename Op, size_t... i>
// _tuple_t<T, n, K> _tuple_pointwise(const _tuple_t<T, n, K1> &p,
//                                    const _tuple_t<T, n, K2> &q, const Op &op,
//                                    std::index_sequence<i...>)
// {
//     return _tuple_t<T, n, K>({op(std::get<i>(p._val),
//     std::get<i>(q._val))...});
// }

template <typename K, typename T, uint8_t n, typename K1, typename K2,
          typename Op>
_tuple_t<T, n, K> _tuple_pointwise(const _tuple_t<T, n, K1> &p,
                                   const _tuple_t<T, n, K2> &q, const Op &op)
{
    // return _tuple_pointwise<K>(p, q, op, std::make_index_sequence<n>());
    _tuple_t<T, n, K> t;
    for (int i = 0; i < n; ++i) { t._val[i] = op(p._val[i], q._val[i]); }
    return t;
}

template <typename K, typename T, uint8_t n, typename K1, typename K2>
_tuple_t<T, n, K> _tuple_add(const _tuple_t<T, n, K1> &p,
                             const _tuple_t<T, n, K2> &q)
{
    return _tuple_pointwise<K>(p, q, std::plus<T>());
}

template <typename K, typename T, uint8_t n, typename K1, typename K2>
_tuple_t<T, n, K> _tuple_sub(const _tuple_t<T, n, K1> &p,
                             const _tuple_t<T, n, K2> &q)
{
    return _tuple_pointwise<K>(p, q, std::minus<T>());
}

template <typename K, typename T, uint8_t n, typename K1, typename K2>
_tuple_t<T, n, K> _tuple_mul(const _tuple_t<T, n, K1> &p,
                             const _tuple_t<T, n, K2> &q)
{
    return _tuple_pointwise<K>(p, q, std::multiplies<T>());
}

template <typename K, typename T, uint8_t n, typename K1, typename K2>
_tuple_t<T, n, K> _tuple_div(const _tuple_t<T, n, K1> &p,
                             const _tuple_t<T, n, K2> &q)
{
    return _tuple_pointwise<K>(p, q, std::divides<T>());
}

template <typename T, uint8_t n, typename K1, typename K2>
T _tuple_dot(const _tuple_t<T, n, K1> &p, const _tuple_t<T, n, K2> &q)
{
    T val = 0;
    for (int i = 0; i < n; ++i) { val += p._val[i] * q._val[i]; }
    return val;
}

template <typename T, uint8_t n, typename K>
_tuple_t<T, n, K> _tuple_scale(const T &r, const _tuple_t<T, n, K> &p)
{
    _tuple_t<T, n, K> t;
    for (int i = 0; i < n; ++i) { t._val[i] = r * p._val[i]; }
    return t;
}

}  // namespace tuple

namespace affine
{
struct Position;
struct Displacement;

template <typename T, uint8_t n>
using point_t = tuple::_tuple_t<T, n, Position>;

template <typename T, uint8_t n>
using vector_t = tuple::_tuple_t<T, n, Displacement>;

template <typename T, uint8_t n> struct tangent_vector_t {
    point_t<T, n> origin;
    point_t<T, n> direction;

    tangent_vector_t(const point_t<T, n> &o, const point_t<T, n> &v)
        : origin(o), direction(v)
    {
    }
};

template <typename T, uint8_t n> struct frame_t {
    std::array<vector_t<T, n>, n> axises;
};

template <typename T, uint8_t n> struct tangent_frame_t {
    point_t<T, n> origin;
    frame_t<T, n> frame;

    tangent_frame_t(const point_t<T, n> &o, const frame_t<T, n> &f)
        : origin(o), frame(f)
    {
    }
};

template <typename T, typename... Args>
point_t<T, sizeof...(Args)> pos(Args... x)
{
    return point_t<T, sizeof...(Args)>(static_cast<T>(x)...);
}

template <typename T, typename... Args>
vector_t<T, sizeof...(Args)> dir(Args... x)
{
    return vector_t<T, sizeof...(Args)>(static_cast<T>(x)...);
}

template <typename T, uint8_t n>
vector_t<T, n> operator-(const point_t<T, n> &p, const point_t<T, n> &q)
{
    return tuple::_tuple_sub<Displacement>(p, q);
}

template <typename T, uint8_t n>
point_t<T, n> operator+(const point_t<T, n> &p, const vector_t<T, n> &q)
{
    return tuple::_tuple_add<Position>(p, q);
}

template <typename T, uint8_t n>
T dot(const vector_t<T, n> &p, const vector_t<T, n> &q)
{
    return tuple::_tuple_dot(p, q);
}

template <typename T, uint8_t n>
vector_t<T, n> operator*(const T &r, const vector_t<T, n> &p)
{
    return tuple::_tuple_scale(r, p);
}

}  // namespace affine
}  // namespace rey::linear

// exported symbols
using scalar_t = double;

using point3 = rey::linear::affine::point_t<scalar_t, 3>;
using vector3 = rey::linear::affine::vector_t<scalar_t, 3>;

point3 pos3(scalar_t x, scalar_t y, scalar_t z)
{
    return rey::linear::affine::pos<scalar_t>(x, y, z);
}

vector3 dir3(scalar_t x, scalar_t y, scalar_t z)
{
    return rey::linear::affine::dir<scalar_t>(x, y, z);
}

scalar_t dot(const vector3 &p, const vector3 &q)
{
    return rey::linear::affine::dot(p, q);
}
