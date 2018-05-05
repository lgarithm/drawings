#include "polyhedron.h"

#include <algorithm>

#include <rey/lang/constants.h>
#include "solids.h"
#include <rey/testing/testing.h>

using std::max_element;

void test_1()
{
    auto R = 3.0;
    auto h = 4.0;
    auto of = oframe();
    auto b = cylinder_surface(R, of);
    auto u = plane(t_vector3(of.o + .5 * h * of.f.Z, of.f.Z));
    auto d = plane(t_vector3(of.o + -.5 * h * of.f.Z, -of.f.Z));

    auto r = ray(origin + 3 * z_axis, -z_axis);

    auto t1 = b.meet(r);
    auto t2 = u.meet(r);
    auto t3 = d.meet(r);

    assert(!t1.has_value());
    assert(t2.has_value());
    assert(!t3.has_value());

    // std::optional<scalarT> ts[] = {t1, t2, t3};
    // auto idx = max_element(ts, ts + 3) - ts;
    // assert(idx == 1);
}

void test_2()
{
    {
        auto c = new cylinder(3, 4);
        auto r = ray(origin + 3 * z_axis, -z_axis);
        auto i = c->intersect(r);
        assert(i.has_value());
        assert(i.value().d == 1);
    }
}

int main()
{
    test(1);
    test(2);
    return 0;
}
