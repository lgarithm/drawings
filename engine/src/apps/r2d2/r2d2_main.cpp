#include "r2d2_model.h"
#include "rey.h"

world* default_test_scene()
{
  auto w = new world;
  *w += new Floor;
  return w;
}

world* test_r2d2_1()
{
  auto w = default_test_scene();
  auto h = 7;
  auto r = 3;
  auto of = oframe(origin, frame(-x_axis, -y_axis, z_axis));
  of = of + .5 * h * of.f.Z;
  *w += new r2d2(r, h, of);
  return w;
}

static const auto examples = atlas({
    {"test_r2d2_1", test_r2d2_1},
  });

int main(int argc, char* argv[]) { return app(argc, argv, examples); }
