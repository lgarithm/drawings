#include "linear.h"

frame::frame() : X(x_axis), Y(y_axis), Z(z_axis) { }

frame::frame(const vector3& x, const vector3& y, const vector3& z)
  : X(x), Y(y), Z(z) { }

oframe::oframe() : o(origin) { }

oframe::oframe(const point3& o, const frame& f) : o(o), f(f) { }

point3 local(const frame& f ,const point3& p)
{ return point3{dot(p, f.X), dot(p, f.Y), dot(p, f.Z)}; }

point3 global(const frame& f, const point3& p)
{ return p.x * f.X + p.y * f.Y + p.z * f.Z; }

point3 local(const oframe& of, const point3& p)
{ return local(of.f, p - of.o); }

point3 global(const oframe& of, const point3& p)
{ return of.o + global(of.f, p); }

t_vector3 local(const oframe& of, const t_vector3& t)
{ return t_vector3{local(of, t.o), local(of.f, t.v)}; }

t_vector3 global(const oframe& of, const t_vector3& t)
{ return t_vector3{global(of, t.o), global(of.f, t.v)}; }

oframe observer(const point3& pos, const point3& focus, const vector3& up)
{
  auto Y = norm(focus - pos);
  auto X = norm(cross(Y, up));
  auto Z = cross(X, Y);
  return oframe{pos, frame{X, Y, Z}};
}

oframe operator+(const oframe& of, const vector3& v)
{ return oframe{of.o + v, of.f}; }

point3 operator+(const t_vector3& t, scalarT d) { return t.o + d * t.v; }
