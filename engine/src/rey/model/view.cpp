#include <rey/model/view.h>

#include <rey/linear/linear.hpp>

namespace
{
camera cam(const vector3 &p, const vector3 &up)
{
    return camera(observer(origin + p, origin, up));
}
}  // namespace

camera::camera()
    : of(observer(origin + z_axis, origin, y_axis)), near(1), aov(45)
{
}
camera::camera(const oframe &of) : of(of), near(1), aov(45) {}

camera top(scalar_t d) { return cam(d * z_axis, y_axis); }
camera bottom(scalar_t d) { return cam(-d * z_axis, -y_axis); }
camera front(scalar_t d) { return cam(-d * y_axis, z_axis); }
camera back(scalar_t d) { return cam(d * y_axis, z_axis); }
camera left(scalar_t d) { return cam(-d * x_axis, z_axis); }
camera right(scalar_t d) { return cam(d * x_axis, z_axis); }
