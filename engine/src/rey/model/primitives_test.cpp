#include <rey/model/primitives.h>

#include <cassert>
#include <cmath>

#include <rey/model/model.h>
#include <rey/testing/testing.h>

void test_0()
{
    {
        auto d =
            r_dis(t_vector3(origin, z_axis), ray{origin + z_axis, -z_axis});
        assert(d.has_value());
        assert(d.value() == 1);
    }
    {
        auto d = r_dis(t_vector3(origin, z_axis), ray{origin + z_axis, z_axis});
        assert(not d.has_value());
    }
    {
        auto d =
            r_dis(t_vector3(origin, -z_axis), ray{origin + z_axis, -z_axis});
        assert(not d.has_value());
    }
}

void test_1()
{
    auto s = sphere(1, pos3(0, 0, 0));
    {
        auto r = ray{pos3(0, 0, 2), norm(vec3(0, 0, -1))};
        auto i = s.intersect(r);
        assert(i.has_value());
        assert(i.value().d == 1);
    }
    {
        auto r = ray{pos3(0, 0, sqrt(2.0)), norm(vec3(1 - 1e-9, 0, -1))};
        auto i = s.intersect(r);
        assert(i.has_value());
    }
    {
        auto r = ray{pos3(0, 0, sqrt(2.1)), norm(vec3(1, 0, -1))};
        auto i = s.intersect(r);
        assert(not i.has_value());
    }
}

void test_2()
{
    intersection i;
    auto a = pos3(1, 0, 0);
    auto b = pos3(0, 1, 0);
    auto c = pos3(0, 0, 1);
    auto t = triangle(a, b, c);
    {
        auto r = ray{pos3(1, 1, 1), norm(vec3(-1, -1, -1))};
        auto i = t.intersect(r);
        assert(i.has_value());
    }
}

int main()
{
    test(0);
    test(1);
    test(2);
    return 0;
}
