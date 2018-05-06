#include <rey/base/debug.h>

#include <cstdio>

#include <map>
#include <string>
#include <typeindex>
#include <typeinfo>

#include <rey/base/params.h>
#include <rey/model/model-builtin.h>
#include <rey/model/model.h>
#include <rey/model/view.h>

void info(const camera &cam)
{
    printf("camera:\n");
    printf("\tpos: %s\n", p_str(cam.of.origin));
    {
        const auto f = cam.of.frame;
        printf("\t.: %s\n", p_str(f.axises[1]));
        printf("\n");

        printf("\t>: %s\n", p_str(f.axises[0]));

        printf("\t^: %s\n", p_str(f.axises[2]));
    }
    printf("\tnear %lf\n", cam.near);
    printf("\taov %lf\n", cam.aov);
}

void show_image_task(const image_task &cfg)
{
    printf("display: %d X %d\n", cfg.d.width, cfg.d.height);
    info(cfg.cam);
    printf("trace depth: %d\n", cfg.dep);
    printf("%lu objects\n", cfg.w.objects.size());
    printf("%lu lights\n", cfg.lights.lights.size());
    for (auto &it : cfg.args) { printf("args: %s\n", it.c_str()); }
}

using dnames = std::map<std::type_index, std::string>;

dnames _names()
{
    dnames mp;
    mp[typeid(plane *)] = "plane";
    mp[typeid(sphere *)] = "sphere";
    mp[typeid(Floor *)] = "Floor";
    mp[typeid(ellipsoid *)] = "ellipsoid";
    return mp;
}

dnames names = _names();

std::string what(const object *po)
{
    auto my_name = names[typeid(po)];
    if (my_name.empty()) {
        my_name = "<" + std::string(typeid(po).name()) + ">";
    }
    return my_name;
}

void info(const world &w)
{
    unsigned char buffer[1024];
    for (const auto &it : w.objects) {
        printf("object{%s}\n", what(it.get()).c_str());
    }
}
