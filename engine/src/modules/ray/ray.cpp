#include "ray.h"

#include <cassert>
#include <cmath>

#include <algorithm>

#include "color.h"
#include "guard.h"
#include "model.h"
#include "profile.h"

using std::max;
using std::min;

static const shader default_shader(black, black);


#define DEFINE_TRACE_FUNC(func_name, TRACE_CODE)                        \
  color func_name(const ray& r, const world& w, const env& e, int dep)  \
  {                                                                     \
    TRACE_CODE;                                                         \
    auto i = nearest(w.objects, r);                                     \
    if (i.just) {                                                       \
      const auto p = r + i.it.d;                                        \
      auto n = t_vector3{p, i.it.o->at(p)};                             \
      n = n + 1e-6 * n.v;                                               \
      const auto s = surface{n, i.it.o->mt(p)};                         \
      return default_shader(s, reflect(s.n.v, r.v), w, e, dep);         \
    } else {                                                            \
      return default_shader.bgc;                                        \
    }                                                                   \
  }


#define NO_TRACE
#define LOG_TRACE                               \
  scope_logger __(__func__);                    \
  log_trace(r, dep);

DEFINE_TRACE_FUNC(trace, NO_TRACE)
DEFINE_TRACE_FUNC(trace_with_log, LOG_TRACE)

shader::shader(const color& b, const color& d) : bgc(b), def(d) {}

color shader::operator()(const surface& s, const vector3& r,
                         const world& w, const env& e, int dep) const
{
  assert_unit(s.n.v, __FILE__, __func__);
  auto nc = def;
  {
    for (const auto& l : e.lights) {
      auto d = len(l.pos - s.n.o);
      auto ldir = norm(l.pos - s.n.o);
      auto j = nearest(w.objects, ray{s.n.o, ldir});
      if (not j.just || d < j.it.d) {
        nc += max(0., dot(ldir, s.n.v)) * s.m.diffuse * l.col +
          pow(max(0., dot(ldir, r)), s.m.roughness) * s.m.specular * l.col;
      }
    }
  }
  auto rc = dep > 0
    ? s.m.reflection * trace(ray{s.n.o, r}, w, e, dep - 1)
    : grey;
  return nc + rc;
}

color rasterize(const world& w, const env& e, const camera& cam,
                const display& d, const viewport& v, int i, int j, int dep)
{
  static const auto f = [](const interval& r, int i, int n)
    { return ((n - i) * r.lo + i * r.hi) / n; };
  auto fc = point3{f(v.xr, i, d.width - 1), cam.near, f(v.yr, j, d.height - 1)};
  auto cc = global(cam.of, fc);
  return trace(ray{cc, norm(cc - cam.of.o)}, w, e, dep);
}

viewport fit(const camera& cam, const display& d)
{
  auto g = [&](scalarT a){ return 2 * cam.near * tan(.5 * a * M_PI / 180); };
  double W = g(cam.aov);
  double H = g(cam.aov);
  double k = .5 * min(W / d.width, H / d.height);
  auto f = [](double l){ return interval{-l, l}; };
  return viewport{f(d.width * k), f(d.height * k)};
}

engine::engine(int dep, const display d) : dep(dep), d(d) { }

color engine::rasterize(const world& w, const env& e, const camera& cam,
                        int i, int j) const
{ return ::rasterize(w, e, cam, d, fit(cam, d), i, j, dep); }

void engine::render(const world& w, const env& e, const camera& cam,
                    const clip& c, unsigned char* p) const
{
  const auto v = fit(cam, d);
  for (unsigned short j=c.h.l; j < c.h.r; ++j) {
    for (unsigned short i=c.w.l; i < c.w.r; ++i) {
      auto pix = rgb(::rasterize(w, e, cam, d, v, i, j, dep));
      *p++ = pix.b;
      *p++ = pix.g;
      *p++ = pix.r;
    }
  }
}

void engine::render(const world& w, const env& e, const camera& cam,
                    unsigned char* buffer) const
{ return render(w, e, cam, clip{range{0, d.width}, range{0, d.height}},
                buffer); }
