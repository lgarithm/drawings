#include "task.h"

#include <vector>
#include <string>

#include "display.h"
#include "point.h"
#include "view.h"

using std::vector;
using std::string;

config::config() : d(XGA),
                   dd(division{1,1}),
                   cam(observer(point3{0,-20,10}, origin, z_axis)),
                   dep(0),
                   t(false),
                   outfile("output.bmp"),
                   outfd(0),
                   buffer(nullptr),
                   bmp_padding(true),
                   use_thread(false),
                   single(false) {}
