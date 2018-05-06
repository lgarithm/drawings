#include <cstdio>

#include <rey/linear/linear.hpp>

void test_1()
{
    point3 o = pos3(0, 0, 0);
    point3 p = pos3(1, 2, 3);
    point3 q = pos3(4, 5, 6);
    vector3 d = p - q;
    point3 r = p + 3.0 * d;
    double l = dot(p - o, q - o);
    printf("%f\n", l);
}

int main()
{
    test_1();
    return 0;
}
