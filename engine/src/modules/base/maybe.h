#ifndef MAYBE_H
#define MAYBE_H

template<typename T>
struct maybe
{
  bool just;
  T it;
};

template<typename T>
maybe<T> nothing() { return maybe<T>{false}; }

template<typename T>
maybe<T> just(const T& it) { return maybe<T>{true, it}; }

#endif  // MAYBE_H
