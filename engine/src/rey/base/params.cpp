#include <rey/base/params.h>

#include <cstdio>
#include <cstring>

#include <map>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

#include <rey/lang/prog.h>
#include <rey/model/model-builtin.h>
#include <rey/model/model.h>
#include <rey/tracing/display.h>

using std::endl;
using std::map;
using std::ostringstream;
using std::string;
using std::unique_ptr;
using std::vector;

// TODO : move to lang/prog

bool parse_display(const char *str, display &d)
{
    auto pos = display_modes.find(str);
    if (pos != display_modes.end()) {
        d = pos->second;
        return true;
    }
    if (sscanf(str, "%huX%hu", &d.width, &d.height) == 2) {
        return d.width <= max_width && d.height <= max_height;
    }
    return false;
}

bool parse_division(const char *str, division &dd)
{
    if (sscanf(str, "%huX%hu", &dd.m, &dd.n) == 2) {
        return dd.m <= 16 && dd.n <= 16;
    }
    return false;
}

bool parse_camera(const char *str, camera &c)
{
    auto t = p_camera(str);
    if (t.has_value()) {
        c.of = t.value().of;
        return true;
    }
    return false;
}

bool parse_depth(const char *str, int &n)
{
    if (sscanf(str, "%d", &n) == 1) return 0 <= n && n <= max_dep;
    return false;
}

object *parse_model(const char *str)
{
    if (HAS_CPP_REGEX) { return p_model(str); }
    return nullptr;
}

bool parse_light(const char *str, light &l)
{
    double x, y, z, r, g, b;
    if (sscanf(str, "light((%lf, %lf, %lf), (%lf, %lf, %lf))", &x, &y, &z, &r,
               &g, &b) == 6) {
        auto f = [](double s) { return 0 <= s && s <= 1; };
        if (!f(r) || !f(g) || !f(b)) return false;
    }
    l.pos = pos3(x, y, z);
    l.col = color(r, g, b);
    return true;
}

bool parse_inline(int argc, const char *const argv[], image_task &cfg)
{
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "-h") == 0) { return false; }
        if (strcmp(argv[i], "-a") == 0) {
            if (++i >= argc) return false;
            int a;
            if (sscanf(argv[i], "%d", &a) == 1) {
                if (0 < a && a < 180) {
                    cfg.cam.aov = a;
                    continue;
                }
            }
            return false;
        }
        if (strcmp(argv[i], "-b") == 0) {
            if (++i >= argc) return false;
            if (not parse_division(argv[i], cfg.dd)) return false;
            continue;
        }
        if (strcmp(argv[i], "-c") == 0) {
            if (++i >= argc) return false;
            if (not parse_camera(argv[i], cfg.cam)) return false;
            continue;
        }
        if (strcmp(argv[i], "-d") == 0) {
            if (++i >= argc) return false;
            display d;
            if (not parse_display(argv[i], d)) return false;
            cfg.d = d;
            continue;
        }
        if (strcmp(argv[i], "-e") == 0) {
            if (++i >= argc) return false;
            clip &c = cfg.c;
            if (sscanf(argv[i], "%hu-%hu,%hu-%hu", &c.w.l, &c.w.r, &c.h.l,
                       &c.h.r) != 4) {
                return false;
            }
            cfg.part = true;
            continue;
        }
        if (strcmp(argv[i], "-l") == 0) {
            if (++i >= argc) return false;
            light l;
            if (not parse_light(argv[i], l)) return false;
            cfg.lights.lights.push_back(l);
            continue;
        }
        if (strcmp(argv[i], "-m") == 0) {
            if (++i >= argc) return false;
            auto po = parse_model(argv[i]);
            if (po == nullptr) return false;
            cfg.w += po;
            continue;
        }
        if (strcmp(argv[i], "-n") == 0) {
            if (++i >= argc) return false;
            int n;
            if (not parse_depth(argv[i], n)) return false;
            cfg.dep = n;
            continue;
        }
        if (strcmp(argv[i], "-o") == 0) {
            if (++i >= argc) return false;
            cfg.outfile = argv[i];
            continue;
        }
        if (strcmp(argv[i], "-p") == 0) {
            cfg.use_thread = true;
            continue;
        }
        if (strcmp(argv[i], "-r") == 0) {
            if (++i >= argc) return false;
            if (sscanf(argv[i], "%hu,%hu", &cfg.j, &cfg.i) != 2) return false;
            cfg.single = true;
            continue;
        }
        if (strcmp(argv[i], "-t") == 0) {
            cfg.t = true;
            continue;
        }
        cfg.args.push_back(argv[i]);
    }
    return true;
}

vector<string> parse_file(const char *name)
{
    printf("from file %s\n", name);
    vector<string> args({"render"});
    char line[1 << 10];
    FILE *fp = fopen(name, "r");
    for (int lino = 0; fgets(line, 999, fp); lino++) {
        if (strncmp("#!", line, 2) == 0 && lino == 0) continue;
        if (strncmp("!!", line, 2) == 0) continue;
        char *p = line;
        int l = strlen(line);
        for (; l > 0 && isspace(line[l - 1]); --l)
            ;
        line[l] = '\0';
        if (l > 0) {
            auto flg = string(line, 2);
            args.push_back(flg);
            if (l > 3) {
                auto val = string(line + 3);
                args.push_back(val);
            }
        }
    }
    fclose(fp);
    return args;
}

bool parse(int argc, const char *const argv[], image_task &cfg)
{
    if (argc > 1 and strcmp(argv[1], "-f") == 0) {
        if (argc > 2) {
            auto args = parse_file(argv[2]);
            int n = args.size();
            const char *a[n];
            for (int i = 0; i < n; ++i) a[i] = args[i].c_str();
            return parse_inline(n, a, cfg);
        }
        return false;
    }
    return parse_inline(argc, argv, cfg);
}

template <typename K, typename T>
T get(const map<K, T> &mp, const K &k, const T &t)
{
    auto pos = mp.find(k);
    return pos != mp.end() ? pos->second : t;
}

bool parse(int argc, const char *const argv[], image_task &cfg,
           const atlas &worlds, world_gen def)
{
    if (not parse(argc, argv, cfg)) { return false; }
    auto fn = def;
    if (not cfg.args.empty()) {
        fn = get<string, world_gen>(worlds, cfg.args[0], def);
        if (fn == nullptr) return false;
    }
    if (fn != nullptr) {
        unique_ptr<world> w(fn());
        for (auto &it : w->objects) { cfg.w += it.release(); }
    }
    return true;
}

void usage(const char *name, const atlas &a)
{
    static const auto usages = {
        "-h, help",
        "-t, test",
        "[-a <aov>] "
        "[-b <division>] "
        "[-c <camera>] "
        "[-d <display>] "
        "[-e <clip>] "
        "[-l <light>] "
        "[-m <object>] "
        "[-n <depth>] "
        "[-o <outfile>] "
        "[-p] "
        "[-r <ji>] "
        "[world]",
        "-f <script.rey.txt>",
    };

    ostringstream options;
    options << "\t<aov> := 1 - 179" << endl
            << "\t<division> := 1X1 - 16X16" << endl
            << "\t<camera> := '(<pos>, <look>, <up>)'" << endl
            << "\t<display> := ";
    for (auto it : display_modes) {
        if (it.second.width <= max_width and it.second.height <= max_height) {
            options << it.first << " | ";
        }
    }
    options << "<w>X<h>" << endl
            << "\t<clip> := w1-w2,h1-h2, e.g. 0-16, 16-32" << endl
            << "\t<depth> := ";
    for (int i = 0; i < max_dep; ++i) { options << i << ", "; }
    options << max_dep << endl
            << "\t<light> := 'light(<pos>, <color>)'" << endl
            << "\t<object> := 'sphere(<size>, <pos>)' "
            << "| 'plane(<pos>, <norm>)'" << endl
            << "\t<color> := '(<r>, <g>, <b>)'" << endl
            << "\t<pos>, <look>, <up> := '(<x>, <y>, <z>)'" << endl
            << "\t<ji> := 0-4095,0-4095" << endl;

    printf("Usage:\n");
    for (auto it : usages) printf("\t%s %s\n", name, it);
    printf("%s", options.str().c_str());
    if (not a.empty()) {
        printf("\t[world]:\n");
        for (auto it : a) printf("\t\t%s\n", it.first.c_str());
        printf("\n");
    }
}
