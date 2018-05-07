#pragma once
#include <memory>

#include <rey/model/model.h>
#include <rey/model/view.h>

struct scene_t {
    world w;
    env lights;
    camera cam;

    scene_t();
};
