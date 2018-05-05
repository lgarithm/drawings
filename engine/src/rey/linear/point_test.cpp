#include <rey/linear/point.h>

#include <cassert>
#include <cmath>

#include <rey/testing/testing.h>

void test_0()
{
    assert(x_axis.x == 1);
    assert(x_axis.y == 0);
    assert(x_axis.z == 0);

    assert(y_axis.x == 0);
    assert(y_axis.y == 1);
    assert(y_axis.z == 0);

    assert(z_axis.x == 0);
    assert(z_axis.y == 0);
    assert(z_axis.z == 1);
}

void test_1()
{
    auto p = vec3(1, 2, 3);
    auto q = vec3(4, 5, 6);
    auto r = vec3(5, 7, 9);
    auto s = p + q;
    assert(r == s);
}

void test_2()
{
    auto p = vec3(1, 1, 1);
    p = norm(p);
    assert(len(p) == 1);
    auto a = vec3(1, 0, 0);
    auto b = vec3(0, 1, 0);
    auto c = vec3(0, 0, 1);
    auto n = norm(a, b, c);
    assert(n.x == n.y);
    assert(n.x == n.z);
    assert(n.x > 0);
    assert(len(n) == 1);
}

void test_3()
{
    auto x = vec3(1, 0, 0);
    auto y = vec3(0, 1, 0);
    auto z = vec3(0, 0, 1);
    assert(cross(x, y) == z);
    assert(cross(y, z) == x);
    assert(cross(z, x) == y);
}

void test_4()
{
    auto u = vec4(1, 0, 0, 1);
    auto v = vec4(0, 1, 0, 1);
    auto w = vec4(0, 0, 1, 1);
    {
        auto o = vec4(0, 0, 0, 1);
        auto m = mat4(u, v, w, o);
        auto d = det(m);
        assert(d == 1);
    }
    {
        auto o = vec4(1. / 3, 1. / 3, 1. / 3, 1);
        auto m = mat4(u, v, w, o);
        auto d = det(m);
        assert_eq(d, 0);
    }
}

void test_5()
{
    auto a = pos3(1, 0, 0);
    auto b = pos3(0, 1, 0);
    auto c = pos3(0, 0, 1);
    auto o = pos3(0, 0, 0);
    {
        auto v = vol6(a, b, c, o);
        assert_eq(v, -1);
    }
    {
        auto v = vol6(o, a, b, c);
        assert_eq(v, 1);
    }
    {
        auto v = area2(o, a, b);
        assert_eq(v, 1);
    }
    {
        auto d = pos3(1, 1, 1);
        auto v = vol6(a, b, c, d);
        assert_eq(v, 2);
    }
}

void test_6()
{
    auto a = pos3(1, 0, 0);
    auto b = pos3(0, 1, 0);
    auto c = pos3(0, 0, 1);
    assert_eq(dis(origin, simplex2{a, b, c}), -sqrt(1.0 / 3));
    assert_eq(dis(point3{1, 1, 1}, simplex2{a, b, c}), 2 * sqrt(1.0 / 3));
}

int main()
{
    test(0);
    test(1);
    test(2);
    test(3);
    test(4);
    test(5);
    test(6);
    return 0;
}
