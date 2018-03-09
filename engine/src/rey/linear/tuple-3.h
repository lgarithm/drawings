#pragma once


#define DEFINE_TUPLE_3(NAME, T, X, Y, Z)                                       \
    struct NAME {                                                              \
        T X, Y, Z;                                                             \
    }

// declarations
#define DECLARE_TUPLE_3_NEG(T, X, Y, Z) T operator-(const T &p)

#define DECLARE_TUPLE_3_EQU(T, X, Y, Z) bool operator==(const T &p, const T &q)

#define DECLARE_TUPLE_3_SCALE(S, T, X, Y, Z) T operator*(S k, const T &p)

#define DECLARE_TUPLE_3_ADD(T, X, Y, Z) T operator+(const T &p, const T &q)

#define DECLARE_TUPLE_3_SUB(T, X, Y, Z) T operator-(const T &p, const T &q)

#define DECLARE_TUPLE_3_MUL(T, X, Y, Z) T operator*(const T &p, const T &q)

#define DECLARE_TUPLE_3_DIV(T, X, Y, Z) T operator/(const T &p, const T &q)

#define DECLARE_TUPLE_3_INC(T, X, Y, Z) void operator+=(T &p, const T &q)

#define DECLARE_TUPLE_3_MOV(T, V, X, Y, Z) T operator+(const T &p, const V &q)

#define DECLARE_TUPLE_3_DIS(T, V, X, Y, Z) V operator-(const T &p, const T &q)

#define DECLARE_TUPLE_3_DOT(S, T, X, Y, Z) S dot(const T &p, const T &q)

#define DECLARE_TUPLE_3_L_1_1(S, T, V, X, Y, Z) S dot(const T &p, const V &q)

// definitions
#define DEFINE_TUPLE_3_NEG(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_NEG(T, X, Y, Z) { return T{-p.X, -p.Y, -p.Z}; }

#define DEFINE_TUPLE_3_EQU(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_EQU(T, X, Y, Z)                                            \
    {                                                                          \
        return p.X == q.X && p.Y == q.Y && p.Z == q.Z;                         \
    }

#define DEFINE_TUPLE_3_SCALE(S, T, X, Y, Z)                                    \
    DECLARE_TUPLE_3_SCALE(S, T, X, Y, Z)                                       \
    {                                                                          \
        return T{k * p.X, k * p.Y, k * p.Z};                                   \
    }

#define DEFINE_TUPLE_3_ADD(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_ADD(T, X, Y, Z)                                            \
    {                                                                          \
        return T{p.X + q.X, p.Y + q.Y, p.Z + q.Z};                             \
    }

#define DEFINE_TUPLE_3_SUB(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_SUB(T, X, Y, Z)                                            \
    {                                                                          \
        return T{p.X - q.X, p.Y - q.Y, p.Z - q.Z};                             \
    }

#define DEFINE_TUPLE_3_MUL(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_MUL(T, X, Y, Z)                                            \
    {                                                                          \
        return T{p.X * q.X, p.Y * q.Y, p.Z * q.Z};                             \
    }

#define DEFINE_TUPLE_3_DIV(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_DIV(T, X, Y, Z)                                            \
    {                                                                          \
        return T{p.X / q.X, p.Y / q.Y, p.Z / q.Z};                             \
    }

#define DEFINE_TUPLE_3_INC(T, X, Y, Z)                                         \
    DECLARE_TUPLE_3_INC(T, X, Y, Z)                                            \
    {                                                                          \
        p.X += q.X;                                                            \
        p.Y += q.Y;                                                            \
        p.Z += q.Z;                                                            \
    }

#define DEFINE_TUPLE_3_MOV(T, V, X, Y, Z)                                      \
    DECLARE_TUPLE_3_MOV(T, V, X, Y, Z)                                         \
    {                                                                          \
        return T{p.X + q.X, p.Y + q.Y, p.Z + q.Z};                             \
    }

#define DEFINE_TUPLE_3_DIS(T, V, X, Y, Z)                                      \
    DECLARE_TUPLE_3_DIS(T, V, X, Y, Z)                                         \
    {                                                                          \
        return V{p.X - q.X, p.Y - q.Y, p.Z - q.Z};                             \
    }

#define DEFINE_TUPLE_3_DOT(S, T, X, Y, Z)                                      \
    DECLARE_TUPLE_3_DOT(S, T, X, Y, Z)                                         \
    {                                                                          \
        return p.X * q.X + p.Y * q.Y + p.Z * q.Z;                              \
    }

#define DEFINE_TUPLE_3_L_1_1(S, T, V, X, Y, Z)                                 \
    DECLARE_TUPLE_3_L_1_1(S, T, V, X, Y, Z)                                    \
    {                                                                          \
        return p.X * q.X + p.Y * q.Y + p.Z * q.Z;                              \
    }


