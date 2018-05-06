#pragma once
#include <array>
#include <cmath>
#include <cstdint>
#include <functional>
#include <string>
#include <utility>

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

template <typename T, uint8_t n, typename K1, typename K2>
void _tuple_inc(_tuple_t<T, n, K1> &p, const _tuple_t<T, n, K2> &q)
{
    for (int i = 0; i < n; ++i) { p._val[i] += q._val[i]; }
}

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
template <typename T, uint8_t n, typename K>
_tuple_t<T, n, K> _tuple_neg(const _tuple_t<T, n, K> &t)
{
    _tuple_t<T, n, K> r;
    for (int i = 0; i < n; ++i) { r._val[i] = -t._val[i]; }
    return r;
}

template <typename T, uint8_t n, typename K>
bool _tuple_eq(const _tuple_t<T, n, K> &p, const _tuple_t<T, n, K> &q)
{
    for (int i = 0; i < n; ++i) {
        if (p._val[i] != q._val[i]) { return false; }
    }
    return true;
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

// TODO: don't override operator for all types
template <typename T, uint8_t n, typename K>
_tuple_t<T, n, K> operator-(const _tuple_t<T, n, K> &t)
{
    return tuple::_tuple_neg(t);
}

template <typename T, uint8_t n, typename K>
_tuple_t<T, n, K> operator*(const T &r, const _tuple_t<T, n, K> &t)
{
    return tuple::_tuple_scale(r, t);
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

// TODO: make it constexpr
template <typename T, uint8_t n> vector_t<T, n> kth_unit(uint8_t i)
{
    vector_t<T, n> v;
    for (int j = 0; j < n; ++j) { v._val[j] = 0; }
    // std::get<i>(v._val) = 1;
    v._val[i] = 1;
    return v;
}

template <typename T, uint8_t n> struct tangent_vector_t {
    point_t<T, n> origin;
    vector_t<T, n> direction;

    tangent_vector_t(const point_t<T, n> &o, const vector_t<T, n> &v)
        : origin(o), direction(v)
    {
    }
};

template <typename T, uint8_t n> struct frame_t {
    using basis_t = std::array<vector_t<T, n>, n>;

    template <size_t... i>
    static basis_t std_basis(const std::index_sequence<i...> &)
    {
        return basis_t({kth_unit<T, sizeof...(i)>(i)...});
    }

    basis_t axises;

    frame_t() : axises(std_basis(std::make_index_sequence<n>())) {}

    template <typename... Args> frame_t(Args... e) : axises({e...})
    {
        static_assert(sizeof...(Args) == n);
    }
};

template <typename T, uint8_t n> struct tangent_frame_t {
    point_t<T, n> origin;
    frame_t<T, n> frame;

    tangent_frame_t() { origin._val.fill(0); }

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
point_t<T, n> operator/(const point_t<T, n> &p, const point_t<T, n> &q)
{
    return tuple::_tuple_div<Position>(p, q);
}

template <typename T, uint8_t n>
point_t<T, n> operator+(const point_t<T, n> &p, const vector_t<T, n> &q)
{
    return tuple::_tuple_add<Position>(p, q);
}

template <typename T, uint8_t n>
vector_t<T, n> operator-(const vector_t<T, n> &p, const vector_t<T, n> &q)
{
    return tuple::_tuple_sub<Displacement>(p, q);
}

template <typename T, uint8_t n>
vector_t<T, n> operator+(const vector_t<T, n> &p, const vector_t<T, n> &q)
{
    return tuple::_tuple_add<Displacement>(p, q);
}

template <typename T, uint8_t n>
T dot(const vector_t<T, n> &p, const vector_t<T, n> &q)
{
    return tuple::_tuple_dot(p, q);
}

template <typename T, uint8_t n> T len(const vector_t<T, n> &p)
{
    return std::sqrt(tuple::_tuple_dot(p, p));
}

// template <typename T, uint8_t n>
// vector_t<T, n> operator*(const T &r, const vector_t<T, n> &p)
// {
//     return tuple::_tuple_scale(r, p);
// }

}  // namespace affine
}  // namespace rey::linear

namespace std
{
template <typename T, uint8_t n, typename K>
string to_string(const rey::linear::tuple::_tuple_t<T, n, K> &t)
{
    std::string ss("(");
    for (int i = 0; i < n; ++i) {
        if (i) { ss += ","; }
        ss += to_string(t._val[i]);
    }
    return ss + ")";
}
}  // namespace std

#define p_str(t) std::to_string(t).c_str()
