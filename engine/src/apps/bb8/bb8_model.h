#ifndef BB8_MODEL_H
#define BB8_MODEL_H

#include "rey.h"

struct bb8_head : bound<sphere>
{
  oframe of;

  bb8_head(double, const oframe&);

  bool in(const point3&) const override;
  material mt(const point3&) const override;
};

struct bb8_body : sphere
{
  oframe of;

  bb8_body(double, const oframe&);

  material mt(const point3&) const override;
};

struct bb8 : object
{
  bb8_head head;
  bb8_body body;

  bb8(double, const oframe&);

  maybe<intersection> intersect(const ray&) const override;
};

#endif  // BB8_MODEL_H
