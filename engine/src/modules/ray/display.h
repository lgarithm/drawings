#ifndef DISPLAY_H
#define DISPLAY_H

struct display{ unsigned short width, height; };

const auto WXGA = display{1280, 800};
const auto WQXGA = display{2560, 1600};
const auto XGA = display{1024, 768};

#endif  // DISPLAY_H
