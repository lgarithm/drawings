#include "task.h"

#include <string>
#include <vector>

#include "display.h"
#include "model.h"
#include "point.h"
#include "view.h"

using std::vector;
using std::string;

image_task::image_task()
    : cam(observer(point3{0, -20, 10}, origin, z_axis)), d(XGA), dep(0),
      single(false), i(0), j(0), part(false), c(full(d)), dd(division{1, 1}),
      buffer(nullptr), outfile("output.bmp"), outfd(0), bmp_padding(true),
      t(false), use_thread(false)
{
}
