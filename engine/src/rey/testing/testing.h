#pragma once


#include <cassert>
#include <cmath>

#include <rey/logger/logger.h>

template <typename T> void assert_eq(T x, T y) { assert(x == y); }

void assert_eq(double x, double y);

#define __2(s) s s
#define __4(s) __2(s s)
#define __8(s) __4(s s)
#define __16(s) __8(s s)
#define __32(s) __16(s s)
#define __64(s) __32(s s)
#define ___(s) __64(s)

#define test(x)                                                                \
    {                                                                          \
        {                                                                      \
            with_c __(1, 42);                                                  \
            printf("%*s", 80, ___("."));                                       \
        }                                                                      \
        printf("\n");                                                          \
        slogger _("test_" #x);                                                 \
        test_##x();                                                            \
    }


