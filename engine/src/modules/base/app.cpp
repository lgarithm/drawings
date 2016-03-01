#include "app.h"

#include <algorithm>
#include <memory>

#include "bmp.h"
#include "debug.h"
#include "display.h"
#include "logger.h"
#include "model.h"
#include "params.h"
#include "ray.h"

using std::unique_ptr;

namespace
{
  clogger lo;
  static const int buffer_size = 3 * max_width * max_height;
  unsigned char buffer[buffer_size];
}

void run(const config& cfg, const scene& s)
{
  if (not cfg.t) {
    lo.log("begin rendering ...");
    engine e(cfg.dep);
    e.render(s, cfg.cam, cfg.v, cfg.d, buffer);
    bmp_head head;
    head.init(cfg.d.width, cfg.d.height);
    lo.log("saving as " + cfg.outfile);
    write_bmp_file(head, buffer, cfg.outfile.c_str());
    lo.log("done");
  }
}
