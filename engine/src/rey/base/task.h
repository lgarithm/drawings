#pragma once

#include <experimental/filesystem>
#include <string>
#include <vector>

#include <rey/model/model.h>
#include <rey/model/view.h>
#include <rey/tracing/display.h>
#include <rey/tracing/tracing.h>

struct image_task {
    std::vector<std::string> args;

    camera cam;
    display d;
    env lights;
    world w;
    int dep;

    bool single;
    unsigned short i, j;
    bool part;
    clip c;
    division dd;

    unsigned char *buffer;
    std::experimental::filesystem::path outfile;
    int outfd;
    bool bmp_padding;

    bool t;
    bool use_thread;

    image_task();
};
