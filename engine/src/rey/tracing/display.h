#pragma once

#include <vector>

struct display {
    unsigned short width, height;
};

struct division {
    unsigned short m, n;
};

struct range {
    unsigned short l, r;
};

struct clip {
    range w, h;
};

static const auto XGA = display{1024, 768};
static const auto WXGA = display{1280, 800};
static const auto WQXGA = display{2560, 1600};
static const auto _1080p = display{1920, 1080};
static const auto __1K = 1024;
static const auto _1KF = display{1 * __1K, 1 * __1K};
static const auto _2KF = display{2 * __1K, 2 * __1K};
static const auto _3KF = display{3 * __1K, 3 * __1K};
static const auto _4KF = display{4 * __1K, 4 * __1K};
static const auto _8KF = display{8 * __1K, 8 * __1K};

struct scheduler {
    display d;
    std::vector<clip> divide();
    std::vector<clip> divide(unsigned short);
    std::vector<clip> divide(unsigned short, unsigned short);
    std::vector<clip> divide(const division &);
};

unsigned ceil_div(unsigned, unsigned);
unsigned size(const display &);
unsigned size(const clip &);
display from_clip(const clip &);
clip full(const display &);
