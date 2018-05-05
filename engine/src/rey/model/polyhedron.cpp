#include <rey/model/polyhedron.h>

#include <cassert>
#include <cmath>

#include <algorithm>
#include <utility>
#include <vector>

#include <rey/arith/arith.h>
#include <rey/model/primitives.h>
#include <rey/model/solids.h>

polygon unit_square(scalarT u = 1)
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
    for (auto &it : idx_m.faces) {
        auto vs = at(idx_m, it);
        auto of = localize(vs);
        polygon p;
        for (auto &v : vs) p.vertices.push_back(point2{v.x, v.y});
        pd.faces.push_back(space_polygon(of, p.vertices));
    }
    return pd;
}

scalarT area(const point2 &o, const point2 &p, const point2 &q)
{
    return .5 * det(p - o, q - o);
}

scalarT area(const polygon &g, const point2 &o)
{
    scalarT s = 0;
    int n = g.vertices.size();
    for (int i = 0; i < n; ++i) {
        s += area(o, g.vertices[i], g.vertices[(i + 1) % n]);
    }
    return s;
}

bool in(const point2 &p, const polygon &g)
{
    scalarT s = 0;
    int n = g.vertices.size();
    for (int i = 0; i < n; ++i) {
        s += fabs(area(p, g.vertices[i], g.vertices[(i + 1) % n]));
    }
    return zero(s - area(g));
}

cylinder::cylinder(scalarT r, scalarT h, const oframe of)
    : b(r, h, of),
      u(r, t_vector3(of.o + .5 * h * of.f.Z, of.f.Z)),
      d(r, t_vector3(of.o + -.5 * h * of.f.Z, -of.f.Z))
{
}

std::optional<intersection> cylinder::intersect(const ray &r) const
{
    return nearest<std::initializer_list<const object *>>({&b, &u, &d}, r);
}

space_polygon::space_polygon(const oframe &of, const std::vector<point2> &vs)
    : of(of)
{
    vertices = vs;
}

std::optional<scalarT> space_polygon::meet(const ray &r) const
{
    auto t = r_dis(t_vector3{of.o, of.f.Z}, r);
    if (t.has_value()) {
        auto p = r + t.value();
        auto q = local(of, p);
        if (in(point2{q.x, q.y}, *this)) { return just<scalarT>(t.value()); }
    }
    return nothing<scalarT>();
}

vector3 space_polygon::at(const point3 &) const { return of.f.Z; }

std::optional<intersection> polyhedron::intersect(const ray &r) const
{
    std::vector<const object *> oo(faces.size());
    for (int i = 0; i < faces.size(); ++i) { oo[i] = &faces[i]; }
    return nearest(oo, r);
}
