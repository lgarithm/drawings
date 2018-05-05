#pragma once


#include <cstdio>

#include <string>

#include <rey/model/model.h>
#include <rey/base/params.h>

#define expand_c(c) c.r, c.g, c.b
#define expand_v(v) v.x, v.y, v.z

template <typename T> void pp(const T &p)
{
    printf("(%f, %f, %f)", expand_v(p));
}

void info(const camera &cam);
void info(const world &w);
void show_image_task(const image_task &cfg);

template <typename T> std::string to_str(const T &p)
{
    char s[64];
    sprintf(s, "(%f, %f, %f)", p.x, p.y, p.z);
    return s;
}


