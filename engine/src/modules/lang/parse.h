#ifndef PARSE_H
#define PARSE_H

#include <cctype>

#include <istream>
#include <string>

struct tokenizer
{
  std::string str;
};

struct skipper
{
  const std::string chs;
  inline skipper(const std::string& chs) : chs(chs) { }
  inline skipper(char ch) : chs(std::string(" ") + ch) { }
};

struct exact_one { const char ch; inline exact_one(char ch) : ch(ch) { } };

struct char_matcher
{ const char ch; inline char_matcher(char ch) : ch(ch) { } };

skipper spaces(' ');
char_matcher comma(',');
char_matcher lb('(');
char_matcher rb(')');

inline std::istream& operator>>(std::istream &in, tokenizer& t)
{
  t.str = "";
  while (isalpha(in.peek())) t.str += in.get();
  return in;
}

inline std::istream& operator>>(std::istream &in, skipper& s)
{ while (s.chs.find(in.peek()) != -1) in.get(); return in; }

inline std::istream& operator>>(std::istream &in, exact_one& c)
{
  char ch; in >> ch;
  if (ch != c.ch) { in.setstate(std::ios_base::failbit); }
  return in;
}

inline std::istream& operator>>(std::istream &in, char_matcher& c)
{ exact_one e(c.ch); return in >> spaces >> e; }

template<typename T> std::istream& operator>>(std::istream &in, T& p)
{ return in >> p.x >> comma >> p.y >> comma >> p.z; }

inline std::istream& operator>>(std::istream &in, color& c)
{ return in >> c.r >> comma >> c.g >> comma >> c.b; }

#endif  // PARSE_H
