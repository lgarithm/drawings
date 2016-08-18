#include "linear.h"

frame::frame() : X(x_axis), Y(y_axis), Z(z_axis) {}

frame::frame(const vector3 &x, const vector3 &y, const vector3 &z)
    : X(x), Y(y), Z(z)
{
}

point3 local(const frame &f, const point3 &p)
{
    return point3{dot(p, f.X), dot(p, f.Y), dot(p, f.Z)};
}

point3 global(const frame &f, const point3 &p)
{
    return origin + p.x * f.X + p.y * f.Y + p.z * f.Z;
}
