#include "ray.h"

double sample(const interval& r, int i, int n)
{ return ((n - i) * r.lo + i * r.hi) / n; }

unsigned char cscale(double s)
{ return (unsigned char) (255 * (s > 1 ? 1 : s)); }

RGB from_color(const color& c) { return RGB{cscale(c.r), cscale(c.g), cscale(c.b)}; }

bool test(const ray& r, const world& w, intersection& i) { return nearest(w, r, i); }

color shade(const intersection& i, const scene& s, int dep)
{
  auto pos = i.r.advance(i.d);
  auto rid = reflect(i.n, i.r.dir);
  auto nc = defaultColor;
  {
    //for (const auto& l : s.lights) {
    for (int idx = 0; idx < s.e.lights.size(); ++idx) {
      const auto& l = s.e.lights[idx];
      auto tol = l.pos - pos;
      auto ldir = norm(tol);
      intersection j;
      if (not test(ray{pos, ldir}, s.w, j) || len(tol) < j.d) {
	auto f = dot(ldir, i.n);
	auto lc = f > 0 ? f * l.col : defaultColor;
	auto df = white;
	nc = nc + df * lc;
      }
    }
  }
  auto rc = dep > 0 ? trace(ray{pos, rid}, s, dep - 1) : grey;
  return nc + rc;
}

color trace(const ray& r, const scene& s, int dep)
{
  intersection i;
  return test(r, s.w, i) ? shade(i, s, dep) : background;
}

struct tracer
{
  const int dep; // = 0;
  tracer(int dep) : dep(dep) {}
  color operator()(const ray& tr, const scene& s) const
  { return trace(tr, s, dep); }
};

tracer default_trace(2);

color rasterize(const scene& s, const viewport& v, const display& d, int i, int j)
{
  auto fc = point2{sample(v.xr, i, d.width - 1), sample(v.yr, j, d.height - 1)};
  auto rd = norm(s.cam.forward + fc.x * s.cam.right + fc.y * s.cam.up);
  auto tr = ray{s.cam.pos, rd};
  return default_trace(tr, s);
}

void render(const scene& s, const viewport& v, const display& d, unsigned char* buffer)
{
  unsigned char *p = buffer;
  for (int j=0; j < d.height; ++j) {
    for (int i=0; i < d.width; ++i) {
      auto c = rasterize(s, v, d, i, j);
      auto pix = from_color(c);
      *p++ = pix.b;
      *p++ = pix.g;
      *p++ = pix.r;
    }
  }
}
