#include <rey/model/model_surface.h>

#include <cassert>
#include <cmath>

#include <rey/arith/arith.h>
#include <rey/base/debug.h>
#include <rey/testing/testing.h>

void test_1()
{
    auto c = cone_surface{1};
    auto n = c.at(pos3(1, 1, sqrt(2)));
    auto z = n - norm(vec3(1, 1, -sqrt(2)));
    printf("%s\n", p_str(z));
    assert_eq(z._val[0], 0);
    assert_eq(z._val[1], 0);
    assert_eq(z._val[2], 0);
}

int main()
{
    test(1);
    return 0;
}
