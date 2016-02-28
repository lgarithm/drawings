#include "linear.h"

point3 local(const frame& f ,const point3& p)
{ return point3{dot(p, f.X), dot(p, f.Y), dot(p, f.Z)}; }

point3 global(const frame& f, const point3& p)
{ return p.x * f.X + p.y * f.Y + p.z * f.Z; }

point3 global(const oframe& of, const point3& p)
{ return of.o + global(of.f, p); }

oframe observer(const point3& pos, const point3& focus, const vector3& up)
{
  auto Z = norm(up);
  auto Y = norm(focus - pos);
  auto X = cross(Y, Z);
  return oframe{pos, frame{X, Y, Z}};
}

point3 operator+(const t_vector& t, pointT d) { return t.o + d * t.v; }
