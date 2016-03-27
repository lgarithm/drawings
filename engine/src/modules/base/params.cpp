#include "params.h"

#include <cstdio>
#include <cstring>

#include <map>
#include <memory>
#include <vector>
#include <string>
#include <sstream>

#include "display.h"
#include "model.h"
#include "model-builtin.h"
#include "prog.h"

using std::endl;
using std::map;
using std::ostringstream;
using std::string;
using std::unique_ptr;
using std::vector;

// TODO : move to lang/prog

bool parse_display(const char * str, display& d)
{
  auto pos = display_modes.find(str);
  if (pos != display_modes.end()) {
    d = pos->second;
    return true;
  }
  if (sscanf(str, "%huX%hu", &d.width, &d.height) == 2) {
    return d.width <= max_width && d.height <= max_height;
  }
  return false;
}

bool parse_division(const char * str, division& dd)
{
  if (sscanf(str, "%huX%hu", &dd.m, &dd.n) == 2) {
    return dd.m <= 16 && dd.n <= 16;
  }
  return false;
}

bool parse_camera(const char * str, camera& c)
{
  point3 p, l;
  vector3 u;
  if (sscanf(str, "((%lf, %lf, %lf), (%lf, %lf, %lf), (%lf, %lf, %lf))",
             &p.x, &p.y, &p.z, &l.x, &l.y, &l.z, &u.x, &u.y, &u.z) == 9) {
    c.of = observer(p, l, u);
    return true;
  }
  return false;
}

bool parse_depth(const char * str, int& n)
{
  if (sscanf(str, "%d", &n) == 1) return 0 <= n && n <= max_dep;
  return false;
}


object* parse_model(const char * str)
{
  if (HAS_CPP_REGEX) { return p_model(str); }
  {
    double s;
    point3 p;
    if (sscanf(str, "sphere(%lf, (%lf, %lf, %lf))", &s, &p.x, &p.y, &p.z) == 4) {
      if (s > 0) return new sphere(s, p);
    }
  }
  {
    if (strcmp(str, "floor") == 0) {
      return new Chessboard;
    }
  }
  {
    t_vector3 n;
    if (sscanf(str, "plane((%lf, %lf, %lf), (%lf, %lf, %lf))",
               &n.o.x, &n.o.y, &n.o.z, &n.v.x, &n.v.y, &n.v.z) == 6) {
      return new plane(n);
    }
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

bool parse(int argc, const char * const argv[], image_task& cfg)
{
  for (int i=1; i < argc; ++i) {
    if (strcmp(argv[i], "-h") == 0) {
      return false;
    }
    if (strcmp(argv[i], "-a") == 0) {
      if (++i >= argc) return false;
      int a;
      if (sscanf(argv[i], "%d", &a) == 1) {
        if (0 < a && a < 180) {
          cfg.cam.aov = a;
          continue;
        }
      }
      return false;
    }
    if (strcmp(argv[i], "-b") == 0) {
      if (++i >= argc) return false;
      if (not parse_division(argv[i], cfg.dd)) return false;
      continue;
    }
    if (strcmp(argv[i], "-c") == 0) {
      if (++i >= argc) return false;
      if (not parse_camera(argv[i], cfg.cam)) return false;
      continue;
    }
    if (strcmp(argv[i], "-d") == 0) {
      if (++i >= argc) return false;
      display d;
      if (not parse_display(argv[i], d)) return false;
      cfg.d = d;
      continue;
    }
    if (strcmp(argv[i], "-e") == 0) {
      if (++i >= argc) return false;
      clip& c = cfg.c;
      if (sscanf(argv[i], "%hu-%hu,%hu-%hu",
                 &c.w.l, &c.w.r, &c.h.l, &c.h.r) != 4) {
        return false;
      }
      cfg.part = true;
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
      cfg.w += po;
      continue;
    }
    if (strcmp(argv[i], "-n") == 0) {
      if (++i >= argc) return false;
      int n;
      if (not parse_depth(argv[i], n)) return false;
      cfg.dep = n;
      continue;
    }
    if (strcmp(argv[i], "-o") == 0) {
      if (++i >= argc) return false;
      cfg.outfile = argv[i];
      continue;
    }
    if (strcmp(argv[i], "-p") == 0) {
      cfg.use_thread = true;
      continue;
    }
    if (strcmp(argv[i], "-r") == 0) {
      if (++i >= argc) return false;
      if (sscanf(argv[i], "%hu,%hu", &cfg.j, &cfg.i) != 2) return false;
      cfg.single = true;
      continue;
    }
    if (strcmp(argv[i], "-t") == 0) {
      cfg.t = true;
      continue;
    }
    cfg.args.push_back(argv[i]);
  }
  return true;
}

template<typename K, typename T>
T get(const map<K, T>& mp, const K& k, const T& t)
{
  auto pos = mp.find(k);
  return pos != mp.end() ? pos->second : t;
}

bool parse(int argc, const char * const argv[], image_task& cfg,
           const atlas& worlds, world_gen def)
{
  if (not parse(argc, argv, cfg)) {
    return false;
  }
  if (not cfg.args.empty()) {
    auto fn = get<string, world_gen>(worlds, cfg.args[0], def);
    if (fn != nullptr) {
      unique_ptr<world> w(fn());
      for (auto& it : w->objects) {
        cfg.w += it.release();
      }
    } else {
      return false;
    }
  }
  return true;
}

void usage(const char * name, const atlas& a)
{
  static const auto usages = {
    "-h, help",
    "-t, test",
    "[-a <aov>] "
    "[-b <division>] "
    "[-c <camera>] "
    "[-d <display>] "
    "[-e <clip>] "
    "[-l <light>] "
    "[-m <object>] "
    "[-n <depth>] "
    "[-o <outfile>] "
    "[-p] "
    "[-r <ji>] "
    "[world]"
  };

  ostringstream options;
  options << "\t<aov> := 1 - 179" << endl
          << "\t<division> := 1X1 - 16X16" << endl
          << "\t<camera> := '(<pos>, <look>, <up>)'" << endl
          << "\t<display> := ";
  for (auto it : display_modes) {
    if (it.second.width <= max_width and it.second.height <= max_height) {
      options << it.first << " | ";
    }
  }
  options << "<w>X<h>" << endl
          << "\t<clip> := w1-w2,h1-h2, e.g. 0-16, 16-32" << endl
          << "\t<depth> := ";
  for (int i=0; i < max_dep; ++i) { options << i << ", "; }
  options << max_dep << endl
          << "\t<light> := 'light(<pos>, <color>)'" << endl
          << "\t<object> := 'sphere(<size>, <pos>)' "
          << "| 'plane(<pos>, <norm>)'" << endl
          << "\t<color> := '(<r>, <g>, <b>)'" << endl
          << "\t<pos>, <look>, <up> := '(<x>, <y>, <z>)'" << endl
          << "\t<ji> := 0-4095,0-4095" << endl;

  printf("Usage:\n");
  for (auto it : usages) printf("\t%s %s\n", name, it);
  printf("%s", options.str().c_str());
  if (not a.empty()) {
    printf("\t[world]:\n");
    for (auto it : a) printf("\t\t%s\n", it.first.c_str());
    printf("\n");
  }
}
