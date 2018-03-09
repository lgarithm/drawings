#include "material.h"

#include "color.h"

material::material()
    : diffuse(white), specular(grey), roughness(200), reflection(.7)
{
}
