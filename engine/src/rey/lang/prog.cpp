#include <rey/lang/prog.h>

#include <regex>
#include <sstream>
#include <string>

#include <rey/base/maybe.h>
#include <rey/lang/constants.h>
#include <rey/lang/parse.h>
#include <rey/model/model-builtin.h>
#include <rey/model/model.h>
#include <rey/optics/color.h>
#include <rey/optics/material.h>

using std::istream;
using std::istringstream;
using std::map;
using std::regex_search;
using std::smatch;
using std::string;

std::regex regex(const string &str)
{
    try {
        return std::regex(str);
    } catch (const std::regex_error &e) {
        printf("%s caught: %s\n", e.what(), str.c_str());
        throw e;
    }
}

std::optional<camera> p_camera(const string &str)
{
    {
        istringstream ss(str);
        point3 p, l;
        vector3 u;
        if (ss >> lb >> lb >> p >> rb >> comma >> lb >> l >> rb >> comma >>
            lb >> u >> rb >> rb) {
            return just(camera(observer(p, l, u)));
        }
    }
    {
        istringstream ss(str);
        tokenizer name;
        if (ss >> spaces >> name) {
            scalarT d;
            if (not(ss >> lb >> d >> rb)) { d = 10; }
            auto cs = build_cameras(d);
            auto it = cs.find(name.str);
            if (it != cs.end()) { return just(it->second); }
        }
    }
    return nothing<camera>();
}

std::optional<color> p_color(const string &str)
{
    {
        auto it = colors.find(str);
        if (it != colors.end()) { return just(it->second); }
    }
    {
        istringstream ss(str);
        color c;
        if (ss >> c) {
            static const auto f = [](colorT x) { return 0 <= x && x <= 1; };
            if (f(c._val[0]) && f(c._val[1]) && f(c._val[1])) {
                return just(c);
            }
        }
    }
    return nothing<color>();
}

std::optional<material> p_material(const string &str)
{
    static const auto pc = string("\\(\\s*([^)]+)\\s*\\)");
    material mt;
    {
        static const auto p = regex("dc" + pc);
        smatch m;
        if (regex_search(str, m, p)) {
            auto c = p_color(m[1].str());
            if (c.has_value()) { mt.diffuse = c.value(); }
        }
    }
    {
        static const auto p = regex("sc" + pc);
        smatch m;
        if (regex_search(str, m, p)) {
            auto c = p_color(m[1].str());
            if (c.has_value()) { mt.specular = c.value(); }
        }
    }
    {
        smatch m;
        if (regex_search(str, m, regex("rf=([0-9\\.]+)"))) {
            colorT rf;
            if (sscanf(m[1].str().c_str(), "%lf", &rf) == 1 && 0 <= rf &&
                rf <= 1) {
                mt.reflection = rf;
            }
        }
    }
    {
        smatch m;
        if (regex_search(str, m, regex("rh=([0-9]+)"))) {
            unsigned short rh;
            if (sscanf(m[1].str().c_str(), "%hu", &rh) == 1 && rh < 0x100) {
                mt.roughness = rh;
            }
        }
    }
    return just(mt);
}

object *p_builtin_model(const string &str)
{
    static const auto p = regex("([a-z0-9]+)\\((.+)\\)");
    smatch m;
    if (regex_search(str, m, p)) {
        const string name = m[1].str();
        istringstream ss(m[2].str());
        if (name == "floor") { return new Chessboard; }
    }
    return nullptr;
}

simple_object *p_s_model(const string &str)
{
    static const auto p = regex("([a-z0-9]+)\\((.+)\\)");
    smatch m;
    if (regex_search(str, m, p)) {
        const string name = m[1].str();
        istringstream ss(m[2].str());
        if (name == "sphere") {
            double s;
            point3 p;
            if (ss >> s >> comma >> lb >> p >> rb) {
                if (s > 0) { return new sphere(s, p); }
            }
        } else if (name == "plane") {
            point3 o;
            vector3 n;
            if (ss >> lb >> o >> rb >> comma >> lb >> n >> rb) {
                return new plane(t_vector3(o, norm(n)));
            }
        }
    }
    return nullptr;
}

object *p_model_regex_unsafe(const string &str)
{
    static const auto p = regex("([^@]+)(@(.+))?");
    smatch m;
    if (regex_search(str, m, p)) {
        material mt;
        if (m.size() == 4) {
            auto mmt = p_material(m[3].str());
            if (mmt.has_value()) mt = mmt.value();
        }
        {
            auto po = p_s_model(m[1].str());
            if (po) {
                po->m = mt;
                return po;
            }
        }
        {
            auto po = p_builtin_model(m[1].str());
            if (po) return po;
        }
    }
    if (str == "floor") { return new Chessboard; }
    return nullptr;
}

object *p_model(const string &str)
{
    try {
        return p_model_regex_unsafe(str);
    } catch (const std::regex_error &e) {
        printf("regex_error caught: %s\n", e.what());
    }
    return nullptr;
}
