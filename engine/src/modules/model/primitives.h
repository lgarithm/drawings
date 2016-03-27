#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "linear.h"
#include "guard.h"
#include "maybe.h"
#include "model.h"
#include "point.h"


struct plane : simple_object
{
  t_vector3 n;

  plane(const t_vector3&);

  maybe<scalarT> meet(const ray&) const override;
  vector3 at(const point3&) const override;
};

struct Floor : plane { Floor(); };

struct disc : plane
{
  scalarT R;
  disc(scalarT, const t_vector3&);
  maybe<scalarT> meet(const ray&) const override;
};

struct Chessboard : plane
{
  double grid_size;
  Chessboard(double=1);
  material mt(const point3&) const override;
};

struct sphere : simple_object
{
  double size;
  point3 pos;

  sphere(double, const point3&);

  maybe<scalarT> meet(const ray&) const override;
  vector3 at(const point3&) const override;
};

struct triangle : plane
{
  const point3 a, b, c;

  triangle(const point3&, const point3&, const point3&);

  maybe<scalarT> meet(const ray&) const override;
};

struct tetrahedron : object
{
  triangle f[4];
  object* subs[4];
  tetrahedron(const point3&, const point3&, const point3&, const point3&);
  maybe<intersection> intersect(const ray&) const override;
};

maybe<scalarT> r_dis(const t_vector3&, const ray&);

#endif  // PRIMITIVE_H
