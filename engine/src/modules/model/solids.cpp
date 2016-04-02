#include "solids.h"

#include <vector>

#include "affine.h"
#include "point.h"

using std::vector;

index_model cuboid(const point3& p, const point3& q)
{
  index_model idx_m;

  {
    const point3 ps[] = {p, q};
    for (int i=0; i < 2; ++i)
      for (int j=0; j < 2; ++j)
        for (int k=0; k < 2; ++k)
          idx_m.vertices.push_back(point3{ps[i].x, ps[j].y, ps[k].z});
  }

  static const unsigned short _cube_faces_indexes[6][4] = {
    {0, 1, 3, 2},
    {4, 6, 7, 5},
    {0, 4, 5, 1},
    {2, 3, 7, 6},
    {0, 2, 6, 4},
    {1, 5, 7, 3},
  };

  static const unsigned short _cube_edges_indexes[12][2] = {
    {0, 1}, {2, 3}, {4, 5}, {6, 7},
    {0, 2}, {2, 6}, {6, 4}, {4, 0},
    {1, 3}, {3, 7}, {7, 5}, {5, 1},
  };

  for (int i=0; i < 6; ++i) {
    face_index f;
    for (int j=0; j < 4; ++j) f.vi.push_back(_cube_faces_indexes[i][j]);
    idx_m.faces.push_back(f);
  }

  return idx_m;
}

index_model cube(scalarT r, const point3& o)
{
  auto a = r / 2;
  auto p = vec3(a, a, a);
  index_model idx_m = cuboid(origin + -p, origin + p);
  for (auto& v : idx_m.vertices) { v = v + (o - origin); }
  return idx_m;
}

vector<point3> at(const index_model& idx_m, const face_index& fi)
{
  vector<point3> vs;
  for (auto i : fi.vi) vs.push_back(idx_m.vertices[i]);
  return vs;
}

oframe localize(vector<point3>& vs)
{
  auto x = norm(vs[1] - vs[0]);
  auto _y = norm(vs[2] - vs[1]);
  auto z = cross(x, _y);
  auto y = cross(z, x);
  auto of = oframe{vs[0], frame{x, y, z}};
  for (auto& v : vs) v = local(of, v);
  return of;
}
