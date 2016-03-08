#ifndef MATERIAL_H
#define MATERIAL_H

#include "color.h"

struct material
{
  color diffuse;
  color specular;
  unsigned char roughness;
  colorT reflection;

  material();

  // TODO
  // static const material
};

#endif  // MATERIAL_H
