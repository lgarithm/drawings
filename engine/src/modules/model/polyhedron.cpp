#include "polyhedron.h"

#include <cmath>

#include <vector>

#include "arith.h"
#include "solids.h"

using std::vector;

polygon unit_square(scalarT u=1)
{
  polygon p;
  p.vertices.push_back(point2{0, 0});
  p.vertices.push_back(point2{u, 0});
  p.vertices.push_back(point2{u, u});
  p.vertices.push_back(point2{0, u});
  return p;
}

polyhedron unit_cube(scalarT u)
{
  polyhedron pd;
  auto idx_m = cube(u, origin);
  for (auto& it : idx_m.faces) {
    auto vs = at(idx_m, it);
    auto of = localize(vs);
    polygon p;
    for (auto& v : vs) p.vertices.push_back(point2{v.x, v.y});
    pd.faces.push_back(space_polygon(of, p.vertices));
  }
  return pd;
}

scalarT area(const point2& o, const point2& p, const point2& q)
{ return .5 * det(p - o, q - o); }

scalarT area(const polygon& g, const point2 o)
{
  scalarT s = 0;
  int n = g.vertices.size();
  for (int i=0; i < n; ++i) {
    s += area(o, g.vertices[i], g.vertices[(i + 1) % n]);
  }
  return s;
}

bool in(const point2& p, const polygon& g)
{
  scalarT s = 0;
  int n = g.vertices.size();
  for (int i=0; i < n; ++i) {
    s += fabs(area(p, g.vertices[i], g.vertices[(i + 1) % n]));
  }
  return zero(s - area(g));
}

maybe<scalarT> dis_r_circle(const t_vector2& r, scalarT s)
{
  return nothing<scalarT>();
}

maybe<point3> cylinder_inf::intersect(const ray& r) const
{
  return nothing<point3>();
}

surface cylinder_inf::at(const point3&) const
{
  return surface{};
}

bool cylinder::intersect(const ray& r, intersection& i) const
{
  auto t = local(of, r);
  auto a = point2{t.o.x, t.o.y};
  auto p = point2{t.v.x, t.v.y};
  //auto d = a - dot(a, p) * p;

  // TODO
  return false;
}

space_polygon::space_polygon(const oframe& of, const std::vector<point2>& vs) :
    of(of) { vertices = vs; }

maybe<point3> space_polygon::intersect(const ray& r) const
{
  auto t = r_dis(t_vector3{of.o, of.f.Z}, r);
  if (t.just) {
    auto p = r + t.it;
    auto q = local(of, p);
    if (in(point2{q.x, q.y}, *this)) {
      return just<point3>(p);
    }
  }
  return nothing<point3>();
}

surface space_polygon::at(const point3& p) const
{
  auto s = surface{t_vector3{of.o, of.f.Z}};
  return s;
}

bool polyhedron::intersect(const ray& r, intersection& i) const
{
  vector<const object*> oo(faces.size());
  for (int i=0; i < faces.size(); ++i) {
    oo[i] = &faces[i];
  }
  return nearest(oo, r, i);
}
