#include <rey/linear/affine.h>

#include <cassert>

#include <rey/testing/testing.h>

void test_1()
{
    oframe of;
    assert(of.o == origin);
    assert(of.f.X == x_axis);
    assert(of.f.Y == y_axis);
    assert(of.f.Z == z_axis);
}

void test_2()
{
    auto a = vec3(-1, 0, 0);
    auto b = vec3(0, -1, 0);
    auto c = vec3(0, 0, -1);
    auto o = pos3(1, 1, 1);
    auto of = oframe{o, frame{a, b, c}};
    auto eq = global(of, o) == origin;
    assert(eq);
}

void test_3()
{
    auto of = oframe{pos3(1, 1, 1), frame{x_axis, y_axis, z_axis}};
    {
        auto p = local(of, pos3(2, 2, 2));
        bool f = p == pos3(1, 1, 1);
        assert(f);
    }
}

int main()
{
    test(1);
    test(2);
    test(3);
    return 0;
}
