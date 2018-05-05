#include <rey/optics/material.h>

#include <rey/optics/color.h>

material::material()
    : diffuse(white), specular(grey), roughness(200), reflection(.7)
{
}
