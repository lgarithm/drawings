#ifndef VIEW_H
#define VIEW_H

#include "affine.h"

struct camera
{
  oframe of;
  scalarT near;
  scalarT aov;
  // TODO: scalarT far;
  // TODO: scalarT aspect = 1;

  camera();
  camera(const oframe&);

  static const camera top(scalarT=10);
  static const camera bottom(scalarT=10);
  static const camera front(scalarT=10);
  static const camera back(scalarT=10);
  static const camera left(scalarT=10);
  static const camera right(scalarT=10);
};

#endif  // VIEW_H
