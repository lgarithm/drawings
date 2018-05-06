#include <rey/tracing/display.h>

#include <cassert>

#include <rey/testing/testing.h>

void test_1()
{
    assert(sizeof(unsigned short) == 2);
    auto c = clip{range{0, 1024}, range{0, 1024}};
    assert(size(c) == 1048576);
    assert(ceil_div(4096 * 4096, 1024 * 1024) == 16);
    assert(ceil_div(4096, 16) == 256);
}

int main()
{
    test(1);
    return 0;
}
