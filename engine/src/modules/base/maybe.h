#ifndef MAYBE_H
#define MAYBE_H

template<typename T> struct maybe { bool just; T it; };

template<typename T> maybe<T> nothing() { return maybe<T>{false}; }

template<typename T> maybe<T> just(const T& it) { return maybe<T>{true, it}; }

template<typename T> bool operator<(const maybe<T>& x, const maybe<T>& y)
{
  if (! x.just) return false;
  if (! y.just) return true;
  return x.it < y.it;
}

#endif  // MAYBE_H
