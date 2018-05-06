#include "examples.h"

#include <apps/bb8/bb8_model.h>
#include <rey/rey>

namespace
{

world *default_test_scene()
{
    auto w = new world;
    *w += new Floor;
    return w;
}

world *example_1()
{
    auto w = new world;
    {
        auto a = pos3(-3, 1, 0);
        auto b = pos3(3, 1, 0);
        auto c = pos3(0, 5, 5);
        *w += new triangle(a, b, c);
    }
    {
        double size = 5;
        auto p = pos3(5, -5, 0);
        auto f = frame(norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis);
        auto of = oframe(p + size * z_axis, f);
        *w += new bb8(size, of);
    }
    return w;
}  // namespace

world *example_2()
{
    auto w = new world;
    auto p = new plane(t_vector3{point3{-5, 0, 5}, x_axis});
    auto q = new plane(t_vector3{point3{5, 0, 5}, -x_axis});
    *w += new Chessboard;
    *w += p;
    *w += q;
    return w;
}

world *test_room()
{
    auto w = new world;
    scalarT x = 100;
    scalarT y = 100;
    scalarT h = 30;
    auto lw = new plane(t_vector3{origin + -.5 * x * x_axis, x_axis});
    auto rw = new plane(t_vector3{origin + .5 * x * x_axis, -x_axis});
    auto fw = new plane(t_vector3{origin + -.5 * y * y_axis, y_axis});
    auto bw = new plane(t_vector3{origin + .5 * y * y_axis, -y_axis});
    auto c = new plane(t_vector3{origin + h * z_axis, -z_axis});
    for (auto it : {lw, rw, fw, bw, c}) { it->m.reflection = .2; }
    lw->m.diffuse = blue;
    rw->m.diffuse = green;
    c->m.diffuse = color{.1, .1, .1};
    *w += new Chessboard;
    *w += lw;
    *w += rw;
    *w += fw;
    *w += bw;
    *w += c;
    return w;
}

world *r2d2_bb8()
{
    auto w = default_test_scene();
    {
        auto h = 7;
        auto r = 3;
        auto p = vec3(-5, 0, 0);
        auto of = oframe(origin + p, frame(-x_axis, -y_axis, z_axis));
        of = of + .5 * h * of.frame.axises[2];
        *w += new r2d2(r, h, of);
    }
    {
        double size = 3.5;
        auto p = point3{5, 0, 0};
        auto f = frame{norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis};
        auto of = oframe(p + size * z_axis, f);
        *w += new bb8(size, of);
    }
    return w;
}

}  // namespace

atlas examples()
{
    atlas mp;
    mp["example_1"] = example_1;
    mp["example_2"] = example_2;
    mp["test_room"] = test_room;
    mp["r2d2_bb8"] = r2d2_bb8;
    return mp;
}
