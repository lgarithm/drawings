#ifndef MODEL_H
#define MODEL_H

#include <memory>
#include <vector>

#include "color.h"
#include "point.h"

struct frame
{
  vector3 X, Y, Z;
  point3 trans(const point3& p);
};

struct oframe { point3 O; frame F; };

struct t_vector{ point3 pos; vector3 norm; };

struct camera
{
  vector3 forward, right, up;
  point3 pos;

  camera(){}
  camera(point3 pos, point3 lookAt);
};

struct ray
{
  point3 start;
  vector3 dir;
  point3 advance(pointT d) const;
};

struct itsec
{
  t_vector t;
  vector3 in;

  double alpha;
  double refraction_ratio;

  double reflect;
  double diffuse;
};

struct intersection
{
  ray r;
  double d;
  vector3 n;

  bool operator<(const intersection& i) const;
};

struct object { virtual bool intersect(const ray&, intersection&) const = 0; };

struct world{ std::vector<std::unique_ptr<object>> objects; };

bool nearest(const world&, const ray&, intersection&);

struct sphere : object
{
  double size;
  point3 pos;
  sphere(double, const point3&);
  bool intersect(const ray&, intersection&) const /* override */;
};

struct light { point3 pos; color col; };

struct env{ std::vector<light> lights; };

struct scene { world w; env e; camera cam; };

#endif  // MODEL_H
