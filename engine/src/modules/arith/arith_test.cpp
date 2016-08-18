#include "arith.h"

#include "testing.h"

void test_1()
{
    {
        auto e = quad_eq{1, 2, 2};
        numericT x1, x2;
        auto n = real_roots(e, x1, x2);
        assert(n == 0);
    }
    {
        auto e = quad_eq{1, 2, 1};
        numericT x1, x2;
        auto n = real_roots(e, x1, x2);
        assert(n == 1);
        assert(x1 == -1);
    }
    {
        auto e = quad_eq{1, -3, 2};
        numericT x1, x2;
        auto n = real_roots(e, x1, x2);
        assert(n == 2);
        assert(x1 == 1);
        assert(x2 == 2);
    }
}

int main()
{
    test(1);
    return 0;
}
