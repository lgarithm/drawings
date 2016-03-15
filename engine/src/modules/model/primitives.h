#ifndef PRIMITIVE_H
#define PRIMITIVE_H

#include "linear.h"
#include "guard.h"
#include "maybe.h"
#include "model.h"
#include "point.h"

maybe<scalarT> r_dis(const t_vector3&, const ray&);

struct plane_alg_impl : simple_object
{
  vector3 n;
  scalarT d;

  plane_alg_impl(const vector3&, scalarT d);

  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

struct Plane : simple_object
{
  t_vector3 n;
  material m;

  Plane(const t_vector3&);

  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

struct disc : Plane
{
  scalarT R;
  disc(scalarT, const t_vector3&);
  maybe<scalarT> meet(const ray&) const override;
};

struct Floor : simple_object
{
  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

struct Chessboard : Floor
{
  double grid_size;

  Chessboard(double=1);
  surface at(const point3&) const override;
};

struct Mirror : Floor { surface at(const point3&) const override; };

struct sphere : simple_object
{
  double size;
  point3 pos;

  sphere(double, const point3&);

  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

struct triangle : simple_object
{
  point3 a,b,c;

  triangle(const point3&, const point3&, const point3&);

  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

#endif  // PRIMITIVE_H
