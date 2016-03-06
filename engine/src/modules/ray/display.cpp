#include "display.h"

#include <algorithm>
#include <map>
#include <string>
#include <vector>

using std::map;
using std::min;
using std::string;
using std::vector;

map<string, display> display_modes()
{
  map<string, display> mp;
  mp["xga"] = XGA;
  mp["wxga"] = WXGA;
  mp["wqxga"] = WQXGA;
  return mp;
}

unsigned ceil_div(unsigned n, unsigned d) { return n / d + (n % d != 0); }

vector<clip> scheduler::divide()
{ return divide(ceil_div(size(d), 1024 * 1024)); }

vector<clip> scheduler::divide(unsigned short n) { return divide(1, n); }

vector<clip> scheduler::divide(unsigned short m, unsigned short n)
{
  vector<clip> a;
  const unsigned short dh = ceil_div(d.height, n);
  const unsigned short dw = ceil_div(d.width, m);
  for (unsigned short j=0; j < d.height; j += dh) {
    const unsigned short j1 = min<unsigned short>(j + dh, d.height);
    for (unsigned short i=0; i < d.width; i += dw) {
      const unsigned short i1 = min<unsigned short>(i + dw, d.width);
      a.push_back(clip{range{i, i1}, range{j, j1}});
    }
  }
  return a;
}

unsigned size(const display& d) { return d.height * d.width; }
unsigned short len(const range& r) { return r.r - r.l; }
unsigned size(const clip& c) { return size(from_clip(c)); }
display from_clip(const clip& c) { return display{len(c.w), len(c.h)}; }
