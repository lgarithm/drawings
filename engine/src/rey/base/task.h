#pragma once


#include <string>
#include <vector>

#include <rey/ray/display.h>
#include <rey/model/model.h>
#include <rey/ray/ray.h>
#include <rey/model/view.h>

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
    std::string outfile;
    int outfd;
    bool bmp_padding;

    bool t;
    bool use_thread;

    image_task();
};


