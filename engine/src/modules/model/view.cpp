#include "view.h"

#include "affine.h"
#include <cstdio>

namespace {
  camera cam(const vector3& p, const vector3& up)
  { return camera(observer(origin + p, origin, up)); }
}

const camera camera::top(scalarT d) { return cam(d * z_axis, y_axis); }
const camera camera::bottom(scalarT d) { return cam(-d * z_axis, -y_axis); }
const camera camera::front(scalarT d) { return cam(-d * y_axis, z_axis); }
const camera camera::back(scalarT d) { return cam(d * y_axis, z_axis); }
const camera camera::left(scalarT d) { return cam(-d * x_axis, z_axis); }
const camera camera::right(scalarT d) { return cam(d * x_axis, z_axis); }

camera::camera() : of(observer(origin + z_axis, origin, y_axis)), near(1), aov(45) { }
camera::camera(const oframe& of) : of(of), near(1), aov(45) { }
