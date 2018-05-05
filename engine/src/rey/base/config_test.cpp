#include <rey/base/config.h>

#include <cassert>
#include <cmath>
#include <cstdio>

void test_1()
{
    printf("%lu\n", sizeof(float));
    printf("%lu\n", sizeof(double));
    printf("%lu\n", sizeof(long double));
}

void test_2()
{
    float d = 0;
    float n = 0 / d;
    assert(std::isnan(n));
}

int main()
{
    test_1();
    test_2();
    return 0;
}
