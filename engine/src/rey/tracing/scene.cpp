#include <rey/linear/linear.hpp>
#include <rey/tracing/scene.hpp>

scene_t::scene_t() : cam(observer(pos3(0, -20, 10), origin, z_axis)) {}
