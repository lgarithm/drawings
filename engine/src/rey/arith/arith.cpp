#include <rey/arith/arith.h>

#include <cmath>
#include <cstdio>

#include <rey/linear/linear.hpp>

numericT eval(const linear_eq &e, numericT x)
{
    return e._val[0] * x + e._val[1];
}

numericT eval(const quad_eq &e, numericT x)
{
    return (e._val[0] * x + e._val[1]) * x + e._val[2];
}

quad_eq operator*(const linear_eq &l, const linear_eq &r)
{
    return quad_eq(l._val[0] * r._val[0],
                   l._val[0] * r._val[1] + l._val[1] * r._val[0],
                   l._val[1] * r._val[1]);
}

quad_eq operator+(const quad_eq &f, const quad_eq &g)
{
    return rey::linear::tuple::_tuple_add<QuadraticEquation>(f, g);
}

quad_eq operator-(const quad_eq &f, const quad_eq &g)
{
    return rey::linear::tuple::_tuple_sub<QuadraticEquation>(f, g);
}

quad_eq sqr(const linear_eq &leq) { return leq * leq; }

unsigned short real_roots(const quad_eq &e, numericT &x1, numericT &x2)
{
    const auto delta = e._val[1] * e._val[1] - 4 * e._val[0] * e._val[2];
    if (delta < 0) { return 0; }
    const auto a2 = 2 * e._val[0];
    if (delta == 0) {
        x1 = x2 = -e._val[1] / a2;
        return 1;
    } else {
        const auto d = std::sqrt(delta);
        x1 = (-e._val[1] - d) / a2;
        x2 = (-e._val[1] + d) / a2;
        return 2;
    }
}

unsigned short positive_roots(const quad_eq &e, numericT &x1, numericT &x2)
{
    const auto n = real_roots(e, x1, x2);
    if (n == 0) { return 0; }
    if (n == 1) { return x1 > 0 ? 1 : 0; }
    if (x1 > 0) { return 2; }
    if (x2 > 0) {
        x1 = x2;
        return 1;
    }
    return 0;
}

bool min_positive_root(const quad_eq &e, numericT &x)
{
    numericT _;
    auto n = positive_roots(e, x, _);
    if (n > 0) {
        auto y = eval(e, x);
        if (std::fabs(y) > 1e-3 || x < 0) {
            fprintf(stderr, "%f X^2 + %f X + %f = 0 @ %f = %f\n", e._val[0],
                    e._val[1], e._val[2], x, y);
        }
    }
    return n > 0;
}
