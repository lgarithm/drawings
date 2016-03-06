#ifndef UTILS_H
#define UTILS_H

#include <map>
#include <string>

using std::map;
using std::string;

template<typename K, typename T>
  T get(const map<K, T>& mp, const K& k, const T& t)
{
  auto pos = mp.find(k);
  return pos != mp.end() ? pos->second : t;
}

#endif  // UTILS_H
