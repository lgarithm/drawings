#include "linear.h"

point3 local(const frame& f ,const point3& p)
{ return point3{dot(p, f.X), dot(p, f.Y), dot(p, f.Z)}; }

point3 global(const frame& f, const point3& p)
{ return p.x * f.X + p.y * f.Y + p.z * f.Z; }

point3 local(const oframe& of, const point3& p)
{ return local(of.f, p - of.o); }

t_vector local(const oframe& of, const t_vector& t)
{ return t_vector{local(of, t.o), local(of, t.v)}; }

point3 global(const oframe& of, const point3& p)
{ return of.o + global(of.f, p); }

oframe observer(const point3& pos, const point3& focus, const vector3& up)
{
  auto Y = norm(focus - pos);
  auto X = norm(cross(Y, up));
  auto Z = cross(X, Y);
  return oframe{pos, frame{X, Y, Z}};
}

oframe operator+(const oframe& of, const vector3& v)
{ return oframe{of.o + v, of.f}; }

point3 operator+(const t_vector& t, scalarT d) { return t.o + d * t.v; }
