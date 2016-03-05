#include <cstdio>

#include <algorithm>
#include <memory>

#include "app.h"
#include "debug.h"
#include "display.h"
#include "params.h"
#include "ray.h"

using std::unique_ptr;

int main(int argc, char* argv[])
{
  config cfg;
  if (not parse(argc, argv, cfg)) {
    usage(argv[0]);
    return 0;
  }
  show_config(cfg);

  scene s;
  s.e = cfg.lights;
  for (auto it : cfg.oo) {
    s.w.objects.push_back(unique_ptr<object>(it));
  }

  run(cfg, s);
  return 0;
}
