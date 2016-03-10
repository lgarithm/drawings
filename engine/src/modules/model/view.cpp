#include "view.h"

const oframe camera::top = observer(origin + z_axis, origin, y_axis);
const oframe camera::front = observer(origin - y_axis, origin, z_axis);

camera::camera() : of(top), near(1), aov(45) { }
camera::camera(const oframe& of) : of(of), near(1), aov(45) { }
