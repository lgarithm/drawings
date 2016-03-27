#ifndef PARSE_H
#define PARSE_H

#include <istream>
#include <string>

struct tokenizer
{

};

struct skipper
{
  const std::string chs;
  inline skipper(const std::string& chs) : chs(chs) { }
  inline skipper(char ch) : chs(std::string(" ") + ch) { }
};

skipper spaces(' ');
skipper comma(',');
skipper lb('(');
skipper rb(')');

std::istream& operator>>(std::istream &in, skipper& s)
{
  for (; s.chs.find(in.peek()) != -1; in.get());
  return in;
}

template<typename T> std::istream& operator>>(std::istream &in, T& p)
{ return in >> p.x >> comma >> p.y >> comma >> p.z; }

inline std::istream& operator>>(std::istream &in, color& c)
{ return in >> c.r >> comma >> c.g >> comma >> c.b; }

#endif  // PARSE_H
