#include "ray.h"

RGB from_color(const color& c)
{
  static const auto f = [](double s)
    { return (unsigned char) (255 * (s > 1 ? 1 : s)); };
  return RGB{f(c.r), f(c.g), f(c.b)};
}

static const shader default_shader(black, black);

color trace(const ray& r, const scene& s, int dep)
{
  intersection i;
  return nearest(s.w, r, i) ? default_shader(i, s, dep) : default_shader.bgc;
}

shader::shader(const color& b, const color& d) : bgc(b), def(d) {}

color shader::operator()(const intersection& i, const scene& s, int dep) const
{
  auto nc = def;
  {
    for (const auto& l : s.e.lights) {
      auto tol = l.pos - i.n.o;
      auto ldir = norm(tol);
      intersection j;
      if (not nearest(s.w, ray{i.n.o, ldir}, j) || len(tol) < j.d) {
        auto f = dot(ldir, i.n.v);
        auto lc = f > 0 ? f * l.col : def;
        auto df = white;
        nc = nc + df * lc;
      }
    }
  }
  auto rc = dep > 0 ? trace(ray{i.n.o, reflect(i.n.v, i.i)}, s, dep - 1) : grey;
  return nc + rc;
}

color rasterize(const scene& s, const camera& cam,
                const viewport& v, const display& d,
                int i, int j, int dep)
{
  static const auto f = [](const interval& r, int i, int n)
    { return ((n - i) * r.lo + i * r.hi) / n; };
  auto fc = point2{f(v.xr, i, d.width - 1), f(v.yr, j, d.height - 1)};
  auto cc = global(cam.of, point3{fc.x, cam.near, fc.y});
  return trace(ray{cc, norm(cc - cam.of.o)}, s, dep);
}

engine::engine(int dep) : dep(dep) { }

void engine::render(const scene& s, const camera& cam,
                    const viewport& v, const display& d,
                    unsigned char* buffer) const
{
  unsigned char *p = buffer;
  for (int j=0; j < d.height; ++j) {
    for (int i=0; i < d.width; ++i) {
      auto c = rasterize(s, cam, v, d, i, j, dep);
      auto pix = from_color(c);
      *p++ = pix.b;
      *p++ = pix.g;
      *p++ = pix.r;
    }
  }
}
