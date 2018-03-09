#pragma once


#define DEFINE_TUPLE_4(NAME, T, X, Y, Z, W)                                    \
    struct NAME {                                                              \
        T X, Y, Z, W;                                                          \
    }


