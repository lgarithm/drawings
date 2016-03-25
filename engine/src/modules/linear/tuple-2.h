#ifndef TUPLE_2_H
#define TUPLE_2_H

#define DEFINE_TUPLE_2(NAME, T, X, Y) struct NAME { T X, Y; }

// declarations
#define DECLARE_TUPLE_2_NEG(T, X, Y)            \
  T operator-(const T& p)

#define DECLARE_TUPLE_2_EQU(T, X, Y)            \
  bool operator==(const T& p, const T& q)

#define DECLARE_TUPLE_2_SCALE(S, T, X, Y)       \
  T operator*(S k, const T& p)

#define DECLARE_TUPLE_2_ADD(T, X, Y)            \
  T operator+(const T& p, const T& q)

#define DECLARE_TUPLE_2_SUB(T, X, Y)            \
  T operator-(const T& p, const T& q)

#define DECLARE_TUPLE_2_INC(T, X, Y)            \
  void operator+=(T& p, const T& q)

#define DECLARE_TUPLE_2_DOT(S, T, X, Y)         \
  S dot(const T& p, const T& q)

#define DECLARE_TUPLE_2_DET(S, T, X, Y)         \
  S det(const T& p, const T& q)

#define DECLARE_TUPLE_2_DIS(T, V, X, Y)         \
  V operator-(const T& p, const T& q)


// definitions
#define DEFINE_TUPLE_2_NEG(T, X, Y)             \
  DECLARE_TUPLE_2_NEG(T, X, Y)                  \
  { return T{-p.X, -p.Y}; }

#define DEFINE_TUPLE_2_EQU(T, X, Y)             \
  DECLARE_TUPLE_2_EQU(T, X, Y)                  \
  { return p.X == q.X && p.y == q.Y; }

#define DEFINE_TUPLE_2_SCALE(S, T, X, Y)        \
  DECLARE_TUPLE_2_SCALE(S, T, X, Y)             \
  { return T{k * p.X, k * p.Y}; }

#define DEFINE_TUPLE_2_ADD(T, X, Y)             \
  DECLARE_TUPLE_2_ADD(T, X, Y)                  \
  { return T{p.X + q.X, p.Y + q.Y}; }

#define DEFINE_TUPLE_2_SUB(T, X, Y)             \
  DECLARE_TUPLE_2_SUB(T, X, Y)                  \
  { return T{p.X - q.X, p.Y - q.Y}; }

#define DEFINE_TUPLE_2_INC(T, X, Y)             \
  DECLARE_TUPLE_2_INC(T, X, Y)                  \
  { p.X += q.X; p.Y += q.Y; }

#define DEFINE_TUPLE_2_DOT(S, T, X, Y)          \
  DECLARE_TUPLE_2_DOT(S, T, X, Y)               \
  { return p.X * q.X + p.Y * q.Y; }

#define DEFINE_TUPLE_2_DET(S, T, X, Y)          \
  DECLARE_TUPLE_2_DET(S, T, X, Y)               \
  { return p.X * q.Y - p.Y * q.X; }

#define DEFINE_TUPLE_2_DIS(T, V, X, Y)          \
  DECLARE_TUPLE_2_DIS(T, V, X, Y)               \
  { return V{p.X - q.X, p.Y - q.Y}; }

#endif  // TUPLE_2_H
