#ifndef BB8_MODEL_H
#define BB8_MODEL_H

#include <map>
#include <string>

#include "rey.h"

std::map<std::string, world_gen> bb8_examples();

struct bb8_head : simple_object
{
  double size;
  oframe of;

  bb8_head(double, const oframe&);

  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

struct bb8_body : simple_object
{
  double size;
  oframe of;

  bb8_body(double, const oframe&);

  maybe<scalarT> meet(const ray&) const override;
  surface at(const point3&) const override;
};

struct bb8 : object
{
//  double size;
//  oframe of;

  bb8_head head;
  bb8_body body;

  bb8(double, const oframe&);

  maybe<intersection> intersect(const ray&) const override;
};

world* bb8_example_1();
world* bb8_example_2();

#endif  // BB8_MODEL_H
