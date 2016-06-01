#include "debug.h"

#include <cstdio>

#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "model.h"
#include "model-builtin.h"
#include "params.h"
#include "view.h"

using std::map;
using std::string;
using std::type_index;


void info(const camera& cam)
{
  printf("camera:\n");
  printf("\tpos: ");
  pp(cam.of.o);
  printf("\n");
  {
    auto f = cam.of.f;
    printf("\t.: ");
    pp(f.Y);
    printf("\n");

    printf("\t>: ");
    pp(f.X);
    printf("\n");

    printf("\t^: ");
    pp(f.Z);
    printf("\n");
  }
  printf("\tnear %lf\n", cam.near);
  printf("\taov %lf\n", cam.aov);
}

void show_image_task(const image_task& cfg)
{
  printf("display: %d X %d\n", cfg.d.width, cfg.d.height);
  info(cfg.cam);
  printf("trace depth: %d\n", cfg.dep);
  printf("%lu objects\n", cfg.w.objects.size());
  printf("%lu lights\n", cfg.lights.lights.size());
  for (auto& it : cfg.args) {
    printf("args: %s\n", it.c_str());
  }
}

typedef map<type_index, string> dnames;

dnames _names()
{
  dnames mp;
  mp[typeid(plane*)] = "plane";
  mp[typeid(sphere*)] = "sphere";
  mp[typeid(Floor*)] = "Floor";
  mp[typeid(ellipsoid*)] = "ellipsoid";
  return mp;
}

dnames names = _names();

string what(const object* po)
{
  auto my_name = names[typeid(po)];
  if (my_name.empty()) {
    my_name = "<" + string(typeid(po).name()) + ">";
  }
  return my_name;
}

void info(const world& w)
{
  unsigned char buffer[1024];
  for (const auto& it : w.objects) {
    printf("object{%s}\n", what(it.get()).c_str());
  }
}