#include "bb8_model.h"
#include "rey.h"

world *bb8_example_1()
{
    auto w = new world;
    double size = 5;
    auto f = frame{norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis};
    auto gg = [&](point3 p) {
        const auto of = oframe{p + size * z_axis, f};
        *w += new bb8(size, of);
    };
    gg(origin);
    *w += new Floor;
    return w;
}

world *bb8_example_2()
{
    auto w = new world;
    double size = 5;
    auto f = frame{norm(x_axis + y_axis), norm(y_axis - x_axis), z_axis};
    auto gg = [&](point3 p) {
        const auto of = oframe{p + size * z_axis, f};
        *w += new bb8(size, of);
    };

    double d = 15;
    for (auto x : {-1, 0, 1}) {
        for (auto y : {-1, 0, 1}) {
            gg(point3{d * x, d * y, 0});
        }
    }
    *w += new Chessboard(5);
    return w;
}

static const auto examples = atlas({
    {"example_1", bb8_example_1}, {"example_2", bb8_example_2},
});

int main(int argc, char *argv[]) { return app(argc, argv, examples); }
