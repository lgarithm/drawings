#include "view.h"

#include "affine.h"

namespace
{
camera cam(const vector3 &p, const vector3 &up)
{
    return camera(observer(origin + p, origin, up));
}
}

camera::camera()
    : of(observer(origin + z_axis, origin, y_axis)), near(1), aov(45)
{
}
camera::camera(const oframe &of) : of(of), near(1), aov(45) {}

camera top(scalarT d) { return cam(d * z_axis, y_axis); }
camera bottom(scalarT d) { return cam(-d * z_axis, -y_axis); }
camera front(scalarT d) { return cam(-d * y_axis, z_axis); }
camera back(scalarT d) { return cam(d * y_axis, z_axis); }
camera left(scalarT d) { return cam(-d * x_axis, z_axis); }
camera right(scalarT d) { return cam(d * x_axis, z_axis); }
