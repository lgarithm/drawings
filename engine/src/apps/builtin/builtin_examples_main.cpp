#include <memory>

#include <map>
#include <string>

#include "builtin_examples.h"
#include "rey.h"

using std::string;
using std::unique_ptr;

const auto builtin_examples = examples();

clogger lo;

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

  auto name = cfg.args.empty() ? "default_test_scene" : cfg.args[0];
  auto fn = get<string, world_gen>(builtin_examples, name, default_test_scene);
  unique_ptr<world> w(fn());

  for (auto& it : w->objects) {
    lo.log("add 1 object from scene", clogger::RED);
    s.w.objects.push_back(unique_ptr<object>(std::move(it)));
  }
  for (auto it : cfg.oo) {
    lo.log("add object from cfg", clogger::RED);
    s.w.objects.push_back(unique_ptr<object>(it));
  }

  run(cfg, s);
  return 0;
}
