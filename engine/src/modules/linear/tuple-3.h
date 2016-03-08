#ifndef TUPLE_3_H
#define TUPLE_3_H

#define DEFINE_TUPLE_3(NAME, T, X, Y, Z) struct NAME { T X, Y, Z; }

#define DEFINE_TUPLE_3_NEGATIVE(T, X, Y, Z)                     \
  T operator-(const T& p) { return T{-p.X, -p.Y, -p.Z}; }

#define DEFINE_TUPLE_3_EQUAL(T, X, Y, Z)                \
  bool operator==(const T& p, const T& q)               \
  { return p.X == q.X && p.y == q.Y && p.Z == q.Z; }

#define DEFINE_TUPLE_3_SCALE(T, P, X, Y, Z)     \
  P operator*(T k, const P& p)                  \
  { return P{k * p.X, k * p.Y, k * p.Z}; }

#define DEFINE_TUPLE_3_PLUS(T, X, Y, Z)                 \
  T operator+(const T& p, const T& q)                   \
  { return T{p.X + q.X, p.Y + q.Y, p.Z + q.Z}; }

#define DEFINE_TUPLE_3_MINUS(T, X, Y, Z)                \
  T operator-(const T& p, const T& q)                   \
  { return T{p.X - q.X, p.Y - q.Y, p.Z - q.Z}; }

#define DEFINE_TUPLE_3_TIMES(T, X, Y, Z)                \
  T operator*(const T& p, const T& q)                   \
  { return T{p.X * q.X, p.Y * q.Y, p.Z * q.Z}; }

#define DEFINE_TUPLE_3_DIV(T, X, Y, Z)                  \
  T operator/(const T& p, const T& q)                   \
  { return T{p.X / q.X, p.Y / q.Y, p.Z / q.Z}; }

#define DEFINE_TUPLE_3_INC(T, X, Y, Z)          \
  void operator+=(T& p, const T& q)             \
  { p.X += q.X; p.Y += q.Y; p.Z += q.Z; }

#define DEFINE_TUPLE_3_DOT(T, P, X, Y, Z)       \
  T dot(const P& p, const P& q)                 \
  { return p.X * q.X + p.Y * q.Y + p.Z * q.Z; }

#endif  // TUPLE_3_H
