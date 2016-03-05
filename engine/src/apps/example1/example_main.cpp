#include <memory>

#include <map>
#include <string>

#include "app.h"
#include "debug.h"
#include "examples.h"
#include "model.h"
#include "params.h"
#include "ray.h"

using std::map;
using std::string;
using std::unique_ptr;

//map<string, world*()> examples;

void init()
{
  //examples["1"] = example_1;
  //examples["2"] = example_2;
}

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
  unique_ptr<world> w(example_1());
  for (auto& it : w->objects) {
    s.w.objects.push_back(unique_ptr<object>(std::move(it)));
  }
  for (auto it : cfg.oo) {
    s.w.objects.push_back(unique_ptr<object>(it));
  }

  run(cfg, s);
  return 0;
}
