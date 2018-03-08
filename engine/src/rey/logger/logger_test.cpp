#include "logger.h"

#include <cstdio>

#include "testing.h"

void test_1()
{
    for (int j = 0; j < 2; ++j) {
        for (int i = 3; i < 5; ++i) {
            for (int k = 0; k < 8; ++k) {
                auto l = i * 10 + k;
                with_c _(j, l);
                printf("[%d;%dm", j, l);
                printf(" ");
            }
            printf("\n");
        }
    }
}

int main()
{
    test(1);
    return 0;
}
