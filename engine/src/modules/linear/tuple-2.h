#ifndef TUPLE_2_H
#define TUPLE_2_H

#define DEFINE_TUPLE_2(NAME, T, X, Y) struct NAME { T X, Y; }

#define DEFINE_TUPLE_2_NEGATIVE(T, X, Y)                \
  T operator-(const T& p) { return T{-p.X, -p.Y}; }

#define DEFINE_TUPLE_2_EQUAL(T, X, Y)           \
  bool operator==(const T& p, const T& q)       \
  { return p.X == q.X && p.y == q.Y; }

#define DEFINE_TUPLE_2_SCALE(T, P, X, Y)        \
  P operator*(T k, const P& p)                  \
  { return P{k * p.X, k * p.Y}; }

#define DEFINE_TUPLE_2_PLUS(T, X, Y)            \
  T operator+(const T& p, const T& q)           \
  { return T{p.X + q.X, p.Y + q.Y}; }

#define DEFINE_TUPLE_2_MINUS(T, X, Y)           \
  T operator-(const T& p, const T& q)           \
  { return T{p.X - q.X, p.Y - q.Y}; }

#define DEFINE_TUPLE_2_INC(T, X, Y)             \
  void operator+=(T& p, const T& q)             \
  { p.X += q.X; p.Y += q.Y; }

#define DEFINE_TUPLE_2_DOT(T, P, X, Y)          \
  T dot(const P& p, const P& q)                 \
  { return p.X * q.X + p.Y * q.Y; }

#define DEFINE_TUPLE_2_DET(T, P, X, Y)                                  \
  T det(const P& p, const P& q) { return p.X * q.Y - p.Y * q.X; }

#endif  // TUPLE_2_H
