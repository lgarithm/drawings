#include <rey/base/app.h>

#include <cassert>
#include <cstdio>

#include <algorithm>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include <unistd.h>

#include <rey/base/debug.h>
#include <rey/base/params.h>
#include <rey/bmp/bmp.h>
#include <rey/logger/logger.h>
#include <rey/model/model.h>
#include <rey/parallel/parallel.h>
#include <rey/profile/tracer.hpp>
#include <rey/tracing/display.h>
#include <rey/tracing/tracing.h>

namespace fs = std::experimental::filesystem;

namespace
{
clogger lo;
static const int buffer_size = 3 * max_width * max_height;
// TODO : !!!!! separate per thread !!!!
unsigned char g_buffer[buffer_size];
}  // namespace

void save(const fs::path &filepath, const display &d,
          const unsigned char *buffer)
{
    bmp_head head;
    head.init(d.width, d.height);
    // fs::create_directory(filepath.parent_path());
    write_bmp_file(head, buffer, filepath.c_str());
}

void stream(int fd, const display &d, const unsigned char *buffer)
{
    bmp_head head;
    head.init(d.width, d.height);
    stream_bmp(head, buffer, fd);
}

void create_render_tasks(const image_task &img_tsk, const engine &e,
                         unsigned char *buffer, std::vector<task *> &ts,
                         std::vector<result *> &rs)
{
    auto sch = scheduler{img_tsk.d};
    auto a = (img_tsk.dd.m > 1 || img_tsk.dd.n > 1) ? sch.divide(img_tsk.dd)
                                                    : sch.divide();
    if (img_tsk.part) a = {img_tsk.c};

    unsigned char *p = buffer;
    auto idx = 0;
    for (auto c : a) {
        {
            with_c _(1, 43);
            printf("\rpreparing part %d/%zu : [%u, %u) X [%u, %u)", ++idx,
                   a.size(), c.w.l, c.w.r, c.h.l, c.h.r);
        }
        auto r = new result;
        rs.push_back(r);
        {
            r->p = p;
            p += 3 * size(c);
        }
        auto tsk = new task(e, img_tsk.w, img_tsk.lights, img_tsk.cam, c, r);
        ts.push_back(tsk);
    }
    printf("\n");
}

int ret_size(const image_task &img_tsk)
{
    auto d = img_tsk.part ? from_clip(img_tsk.c) : img_tsk.d;
    int s = size(d) * 3;
    return img_tsk.bmp_padding ? s + 54 : s;
}

#define UNCHECK(expr) ({ auto _ = expr; })

void save_results(const image_task &img_tsk, const unsigned char *buffer,
                  const std::vector<result *> &rs)
{
    auto d = img_tsk.part ? from_clip(img_tsk.c) : img_tsk.d;

    if (img_tsk.outfd > 0) {
        if (!img_tsk.bmp_padding) {
            lo.log("streamming raw pixel");
            printf("will send %d bytes\n", size(d) * 3);
            UNCHECK(write(img_tsk.outfd, buffer, size(d) * 3));
        } else {
            lo.log("streamming bmp file");
            printf("will send %d bytes\n", size(d) * 3 + 54);
            stream(img_tsk.outfd, d, buffer);
        }
        lo.log("end streamming");
    } else if (img_tsk.dd.m > 1 && img_tsk.dd.n > 1) {
        for (auto it : rs) {
            char name[64];
            sprintf(name, "%s.%dX%d.part.[%d-%d)X[%d-%d).bmp",
                    img_tsk.outfile.c_str(), img_tsk.dd.m, img_tsk.dd.n,
                    it->c.w.l, it->c.w.r, it->c.h.l, it->c.h.r);
            lo.log("saving as " + std::string(name));
            save(name, from_clip(it->c), it->p);
        }
    } else {
        lo.log("saving as " + img_tsk.outfile.string());
        save(img_tsk.outfile, d, buffer);
    }
}

void run(const image_task &img_tsk)
{
    TRACE(__func__);
    if (img_tsk.t) return;
    engine e(img_tsk.dep, img_tsk.d);
    if (img_tsk.single) {
        auto g = e.rasterize(img_tsk.w, img_tsk.lights, img_tsk.cam, img_tsk.i,
                             img_tsk.j);
        auto p = rgb(g);
        printf("pix[%d, %d] = %s # %02x %02x %02x | %d %d %d\n", img_tsk.j,
               img_tsk.i, p_str(g), p.r, p.g, p.b, p.r, p.g, p.b);
        return;
    }

    std::vector<result *> rs;
    std::vector<task *> ts;
    unsigned char *buffer = img_tsk.buffer ? img_tsk.buffer : g_buffer;
    create_render_tasks(img_tsk, e, buffer, ts, rs);

    lo.log("begin rendering ...");
    run_tasks(ts, img_tsk.use_thread);
    lo.log("end rendering.");
    save_results(img_tsk, buffer, rs);
    lo.log("image task done.");
}

int app(int argc, const char *const argv[], const atlas &worlds, world_gen def)
{
    printf("\e[1;43mparsing args ...\e[m\n");
    image_task img_tsk;
    if (not parse(argc, argv, img_tsk, worlds, def)) {
        usage(argv[0], worlds);
        for (int i = 0; i < argc; ++i) {
            printf("\e[1;33mX-Rey\e[m: %s\n", argv[i]);
        }
        printf("\n");
        return 0;
    }
    if (not img_tsk.outfile.empty()) {
        printf("\e[1;34mrendering %s ...\e[m\n", img_tsk.outfile.c_str());
    }
    show_image_task(img_tsk);
    run(img_tsk);
    printf("\e[1;42mDONE\e[m\n");
    return 0;
}
