#ifndef VIEW_H
#define VIEW_H

#include "linear.h"

struct camera
{
  oframe of;
  scalarT near;
  scalarT aov;
  // TODO: scalarT far;
  // TODO: scalarT aspect = 1;

  camera();
  camera(const oframe&);

  static const oframe top;
  static const oframe front;
};


#endif  // VIEW_H
