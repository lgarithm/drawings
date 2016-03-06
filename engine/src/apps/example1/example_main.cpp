#include <memory>

#include <map>
#include <string>

#include "examples.h"
#include "rey.h"

using std::string;
using std::unique_ptr;

const auto builtin_examples = examples();

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

  auto name = cfg.args.empty() ? "example_1" : cfg.args[0];
  auto fn = get<string, world_gen>(builtin_examples, name, example_1);
  unique_ptr<world> w(fn());

  for (auto& it : w->objects) {
    s.w.objects.push_back(unique_ptr<object>(std::move(it)));
  }
  for (auto it : cfg.oo) {
    s.w.objects.push_back(unique_ptr<object>(it));
  }

  run(cfg, s);
  return 0;
}
