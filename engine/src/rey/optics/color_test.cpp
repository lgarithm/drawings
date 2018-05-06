#include <rey/optics/color.h>

#include <rey/testing/testing.h>

void test_1()
{
    auto c = color{.1, .1, .1};
    auto d = color{.5, .5, .5};
    c += d;
    assert(c._val[0] == .6);
    assert(c._val[1] == .6);
    assert(c._val[2] == .6);
}

int main()
{
    test(1);
    return 0;
}
