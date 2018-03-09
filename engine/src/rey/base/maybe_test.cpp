#include "maybe.h"

#include "testing.h"

void test_1()
{
    {
        auto a = just(1);
        auto b = just(2);
        assert(a < b);
    }
    {
        auto a = nothing<int>();
        auto b = just(1);
        assert(not(a < b));
    }
    {
        auto a = just(1);
        auto b = nothing<int>();
        assert(a < b);
    }
}

int main()
{
    test(1);
    return 0;
}
