#ifndef UTILS_H
#define UTILS_H

#include <algorithm>
#include <map>
#include <string>

using std::map;
using std::min;
using std::string;

template<typename K, typename T>
  T get(const map<K, T>& mp, const K& k, const T& t)
{
  auto pos = mp.find(k);
  return pos != mp.end() ? pos->second : t;
}

template<typename T>
T min3(const T& a, const T& b, const T& c) { return min(a, min(b, c)); }

#endif  // UTILS_H
