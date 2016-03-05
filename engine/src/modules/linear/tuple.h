#ifndef TUPLE_H
#define TUPLE_H

#define DEFINE_TUPLE_2(NAME, T, X, Y) struct NAME { T X,Y; }

#define DEFINE_TUPLE_3(NAME, T, X, Y, Z) struct NAME { T X,Y,Z; }

#define DEFINE_TUPLE_4(NAME, T, X, Y, Z, W) struct NAME { T X,Y,Z,W; }

#define DEFINE_TUPLE3_EQUAL(T, X, Y, Z) \
  bool operator==(const T& p, const T& q) \
  { return p.X == q.X && p.y == q.Y && p.Z == q.Z; }

#define DEFINE_TUPLE_3_SCALE(T, P, X, Y, Z)	\
  P operator*(T t, const P& p) \
  { return P{t * p.X, t * p.Y, t * p.Z}; }

#define DEFINE_TUPLE_3_PLUS(T, X, Y, Z)	\
  T operator+(const T& p, const T& q) \
  { return T{p.X + q.X, p.Y + q.Y, p.Z + q.Z}; }

#define DEFINE_TUPLE_3_MINUS(T, X, Y, Z) \
  T operator-(const T& p, const T& q) \
  { return T{p.X - q.X, p.Y - q.Y, p.Z - q.Z}; }

#define DEFINE_TUPLE_3_TIMES(T, X, Y, Z) \
  T operator*(const T& p, const T& q) \
  { return T{p.X * q.X, p.Y * q.Y, p.Z * q.Z}; }

#define DEFINE_TUPLE_3_INC(T, X, Y, Z) \
  void operator+=(T& p, const T& q) \
  { p.X += q.X; p.Y += q.Y; p.Z += q.Z; }

#endif  // TUPLE_H
