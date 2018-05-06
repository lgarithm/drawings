#include <rey/model/view.h>

#include <rey/testing/testing.h>

void test_1()
{
    auto t = [](const camera &c, scalar_t d) {
        auto p = local(c.of, origin);
        assert(p._val[0] == 0);
        assert(p._val[2] == 0);
        assert(p._val[1] == d);
    };
    t(top(99), 99);
    t(bottom(99), 99);
    t(front(99), 99);
    t(back(99), 99);
    t(left(99), 99);
    t(right(99), 99);
}

int main()
{
    test(1);
    return 0;
}
