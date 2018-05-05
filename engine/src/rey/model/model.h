#pragma once

#include <map>
#include <memory>
#include <utility>
#include <vector>

#include <rey/base/maybe.h>
#include <rey/linear/affine.h>
#include <rey/linear/point.h>
#include <rey/optics/color.h>
#include <rey/optics/material.h>

typedef t_vector3 ray;

struct neibourhood {
    virtual vector3 at(const point3 &) const = 0;
    virtual material mt(const point3 &) const = 0;
};

struct intersection {
    const neibourhood *o;
    scalarT d;
};

struct object {
    virtual maybe<intersection> intersect(const ray &) const = 0;
    virtual ~object() {}
};

typedef object *(*obj_gen)();

struct complex_object : object, neibourhood {
    maybe<intersection> intersect(const ray &) const override;
    virtual maybe<scalarT> meet(const ray &) const = 0;
};

struct simple_object : complex_object {
    material m;
    inline material mt(const point3 &) const override { return m; }
};

template <typename T> struct bound : T {
    bound(const T &g) : T(g) {}
    maybe<intersection> intersect(const ray &r) const override
    {
        auto t = T::meet(r);
        if (t.just and in(r + t.it)) { return just(intersection{this, t.it}); }
        return nothing<intersection>();
    }
    virtual bool in(const point3 &)const = 0;
};

struct world {
    std::vector<std::unique_ptr<object>> objects;
};

void operator+=(world &, object *);
typedef world *(*world_gen)();
typedef std::map<std::string, world_gen> atlas;

inline bool near_than(const maybe<intersection> &i,
                      const maybe<intersection> &j)
{
    if (!i.just) { return false; }
    if (!j.just) { return true; }
    return i.it.d < j.it.d;
}

template <typename T> maybe<intersection> nearest(const T &oo, const ray &r)
{
    auto i = nothing<intersection>();
    for (const auto &it : oo) {
        auto j = it->intersect(r);
        if (near_than(j, i)) i = j;
    }
    return i;
}

struct light {
    point3 pos;
    color col;
};

struct env {
    std::vector<light> lights;
};

typedef env *(*env_gen)();
