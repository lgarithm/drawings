#ifndef DISPLAY_H
#define DISPLAY_H

#include <vector>

struct display{ unsigned short width, height; };
struct division{ unsigned short m, n; };
struct range{ unsigned short l, r; };
struct clip{ range w, h; };

const auto WXGA = display{1280, 800};
const auto WQXGA = display{2560, 1600};
const auto XGA = display{1024, 768};

struct scheduler
{
  display d;
  std::vector<clip> divide();
  std::vector<clip> divide(unsigned short);
  std::vector<clip> divide(unsigned short, unsigned short);
};

unsigned ceil_div(unsigned, unsigned);
unsigned size(const display&);
unsigned size(const clip&);
display from_clip(const clip&);

#endif  // DISPLAY_H