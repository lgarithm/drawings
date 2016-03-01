#ifndef MAYBE_H
#define MAYBE_H

template<typename T >
struct maybe
{
  bool nothing;
  T just;
};

#endif  // MAYBE_H
