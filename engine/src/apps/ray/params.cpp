#include "params.h"

#include <cstdio>
#include <cstring>

#include <map>
#include <vector>
#include <string>

#include "display.h"
#include "model.h"
#include "ray.h"

using std::map;
using std::vector;
using std::string;

map<string, display> _display_modes()
{
  map<string, display> mp;
  mp["xga"] = XGA;
  mp["wxga"] = WXGA;
  mp["wqxga"] = WQXGA;
  return mp;
}

const map<string, display> DISPLAY_MODES = _display_modes();

viewport center(double width, double height)
{
  auto c = [](double x){ return interval{-x, x}; };
  return viewport{c(.5 * width), c(.5 * height)};
}

config def_config() {
  config cfg;
  cfg.d = XGA;
  cfg.v = center(10, 10);
  cfg.cam = camera{observer(point3{0,-20,10}, origin, z_axis), 1};
  cfg.dep = 0;
  return cfg;
}

env def_env()
{
  env e;
  double h = 10;
  double x = 20;
  double y = 20;
  e.lights.push_back(light{point3{-x, y, h}, red});
  e.lights.push_back(light{point3{x, y, h}, red});
  e.lights.push_back(light{point3{x, -y, h}, red});
  e.lights.push_back(light{point3{-x, -y, h}, red});
  return e;
}

bool parse_display(const char * str, display& d)
{
  auto pos = DISPLAY_MODES.find(str);
  if (pos != DISPLAY_MODES.end()) {
    d = pos->second;
    return true;
  }
  if (sscanf(str, "%huX%hu", &d.width, &d.height) == 2) {
    return d.width <= max_width && d.height <= max_height;
  }
  return false;
}

bool parse_viewport(const char * str, viewport& v)
{
  return sscanf(str, "[[%lf, %lf], [%lf, %lf]]", &v.xr.lo, &v.xr.hi, &v.yr.lo, &v.yr.hi) == 4;
}

bool parse_camera(const char * str, camera& c)
{
  point3 p, l, u;
  if (sscanf(str, "((%lf, %lf, %lf), (%lf, %lf, %lf), (%lf, %lf, %lf))",
	     &p.x, &p.y, &p.z, &l.x, &l.y, &l.z, &u.x, &u.y, &u.z) == 9) {
    c.of = observer(p, l, u);
    return true;
  }
  return false;
}

bool parse_depth(const char * str, int& n)
{
  if (sscanf(str, "%d", &n) == 1) return 0 <= n && n <= 5;
  return false;
}

object* parse_model(const char * str)
{
  double s, x, y, z;
  if (sscanf(str, "sphere(%lf, (%lf, %lf, %lf))", &s, &x, &y, &z) == 4) {
    if (s > 0) return new sphere{s, vec3(x, y, z)};
  }
  if (strcmp(str, "floor") == 0) {
    return new Floor;
  }
  return nullptr;
}

bool parse_light(const char * str, light& l)
{
  if (sscanf(str, "light((%lf, %lf, %lf), (%lf, %lf, %lf))",
	     &l.pos.x, &l.pos.y, &l.pos.z,
	     &l.col.r, &l.col.g, &l.col.b) == 6) {
    auto f = [](double s) { return 0 <= s && s <= 1; };
    if (f(l.col.r) && f(l.col.g) && f(l.col.b)) return true;
  }
  return false;
}

bool parse(int argc, const char * const argv[], config& cfg)
{
  for (int i=1; i < argc; ++i) {
    if (strcmp(argv[i], "-h") == 0) {
      return false;
    }
    if (strcmp(argv[i], "-d") == 0) {
      if (++i >= argc) return false;
      display d;
      if (not parse_display(argv[i], d)) return false;
      cfg.d = d;
      continue;
    }
    if (strcmp(argv[i], "-v") == 0) {
      if (++i >= argc) return false;
      viewport v;
      if (not parse_viewport(argv[i], v)) return false;
      cfg.v = v;
      continue;
    }
    if (strcmp(argv[i], "-c") == 0) {
      if (++i >= argc) return false;
      if (not parse_camera(argv[i], cfg.cam)) return false;
      continue;
    }
    if (strcmp(argv[i], "-n") == 0) {
      if (++i >= argc) return false;
      int n;
      if (not parse_depth(argv[i], n)) return false;
      cfg.dep = n;
      continue;
    }
    if (strcmp(argv[i], "-l") == 0) {
      if (++i >= argc) return false;
      light l;
      if (not parse_light(argv[i], l)) return false;
      cfg.lights.lights.push_back(l);
      continue;
    }
    if (strcmp(argv[i], "-m") == 0) {
      if (++i >= argc) return false;
      auto po = parse_model(argv[i]);
      if (po == nullptr) return false;
      cfg.oo.push_back(po);
      continue;
    }
    if (strcmp(argv[i], "-t") == 0) {
      cfg.t = true;
      continue;
    }
    return false;
  }
  return true;
}

void usage(const char * name)
{
  static const char* usages[] = {
    "-h, help",
    "[-d <display>] "
    "[-v <viewport>] "
    "[-c <camera>]"
    "[-n <depth>]"
    "[-m <object>] "
    "[-l <light>]",
  };
  static const char* options[] = {
    "<display> := xga | wxga | wqxga | <w>X<h>",
    "<viewport> := '[[x1, x2], [y1, y2]]'",
    "<camera> := '(<pos>, <look>, <up>)'",
    "<depth> := 0,1,2,3,4,5",
    "<object> := 'sphere(<size>, <pos>)'",
    "<light> := 'light(<pos>, <color>)'",
    "<pos>, <look>, <up> := '(<x>, <y>, <z>)'",
    "<color> := '(<r>, <g>, <b>)'",
  };
  printf("Usage:\n");
  for (auto it : usages) printf("\t%s %s\n", name, it);
  for (auto it : options) printf("\t%s\n", it);
  printf("\n");
}
