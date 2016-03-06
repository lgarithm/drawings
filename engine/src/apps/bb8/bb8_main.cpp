#include <memory>

#include <string>

#include "bb8_model.h"
#include "rey.h"

using std::string;
using std::unique_ptr;

clogger lo;

const auto examples = bb8_examples();

int main(int argc, char* argv[])
{
  config cfg;
  if (not parse(argc, argv, cfg)) {
    usage(argv[0]);
    return 0;
  }
  if (cfg.lights.lights.empty()) {
    // TODO: default lights
  }
  show_config(cfg);

  if (cfg.args.empty()) { cfg.args.push_back("example_2"); }
  auto fn = get<string, world_gen>(examples, cfg.args[0], bb8_example_2);
  unique_ptr<world> w(fn());

  scene s;
  s.e = cfg.lights;
  for (auto& it : w->objects) {
    lo.log("add 1 object", clogger::RED);
    s.w.objects.push_back(unique_ptr<object>(std::move(it)));
  }

  run(cfg, s);
  return 0;
}
