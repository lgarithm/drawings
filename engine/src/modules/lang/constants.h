#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <map>
#include <string>

#include "color.h"
#include "display.h"
#include "view.h"

static const auto colors = std::map<std::string, color>({
    {"black", black},
    {"red", red},
    {"green", green},
    {"blue", blue},
    {"yellow", yellow},
    {"orange", orange},
    {"white", white},
    {"grey", grey},
});

static const auto display_modes = std::map<std::string, display>({
    {"xga", XGA},
    {"wxga", WXGA},
    {"wqxga", WQXGA},
    {"1080p", _1080p},
    {"1kf", _1KF},
    {"2kf", _2KF},
    {"3kf", _3KF},
    {"4kf", _4KF},
    {"8kf", _8KF},
});

std::map<std::string, camera> build_cameras(scalarT d = 10);
// static const auto cameras = build_cameras();  // ?? !!

#endif // CONSTANTS_H
