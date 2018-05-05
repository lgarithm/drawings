#include <rey/lang/prog.h>

#include <cassert>

#include <rey/base/debug.h>
#include <rey/testing/testing.h>

void test_1()
{
    {
        auto m = p_material("dc(red)");
        assert(m.just);
        assert(m.it.diffuse == red);
    }
    {
        auto m = p_material("dc(1, 0, 0)");
        assert(m.just);
        assert(m.it.diffuse == red);
    }
    {
        auto m = p_material("sc(1, 0, 0)");
        assert(m.just);
        assert(m.it.specular == red);
    }
}

void test_2()
{
    {
        auto po = p_model("sphere(1, (1,2,3)) @ ");
    }
}

void test_3()
{
    static const char *succ[] = {
        "sphere(1,(1,1,1))", "sphere(1, (1, 1, 1))", "sphere(3, (-4,0,3))",
    };
    for (auto it : succ) {
        assert(p_model(it));
    }
}

void test_4()
{
    static const char *fail[] = {
        "sphere(1)", "sphere (1, (1, 1, 1))",
    };
    for (auto it : fail) {
        assert(p_model(it) == nullptr);
    }
}

int main()
{
    if (not HAS_CPP_REGEX) {
        return 0;
    }
    test(1);
    test(2);
    test(3);
    test(4);
    return 0;
}
