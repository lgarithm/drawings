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
  cfg.cam = camera(vec3(0, -20, 5), vec3(0, 0, 5));
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

bool parse_viewport(const char * str, viewport& v)
{
  if (sscanf(str, "[[%lf, %lf], [%lf, %lf]]", &v.xr.lo, &v.xr.hi, &v.yr.lo, &v.yr.hi) == 4) {
    return true;
  }
  return false;
}

object* parse_model(const char * str)
{
  double s, x, y, z;
  if (sscanf(str, "sphere(%lf, (%lf, %lf, %lf))", &s, &x, &y, &z) == 4) {
    if (s > 0) return new sphere{s, vec3(x, y, z)};
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
      auto pos = DISPLAY_MODES.find(argv[i]);
      if (pos == DISPLAY_MODES.end()) return false;
      cfg.d = pos->second;
      continue;
    }
    if (strcmp(argv[i], "-v") == 0) {
      if (++i >= argc) return false;
      viewport v;
      if (not parse_viewport(argv[i], v)) return false;
      cfg.v = v;
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
    "[-m <object>] "
    "[-l <light>]",
  };
  static const char* options[] = {
    "<display> := xga | wxga | wqxga",
    "<viewport> := '[[x1, x2], [y1, y2]]'"
    "<object> := 'sphere(<size>, <pos>)'",
    "<light> := 'light(<pos>, <color>)'",
    "<pos> := '(<x>, <y>, <z>)'",
    "<color> := '(<r>, <g>, <b>)'",
  };
  printf("Usage:\n");
  for (auto it : usages) {
    printf("\t%s %s\n", name, it);
  }
  for (auto it : options) {
    printf("\t%s\n", it);
  }
  printf("\n");
}
