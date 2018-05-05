#include <rey/base/guard.h>

#include <cassert>
#include <cmath>
#include <cstdio>

#include <map>
#include <string>

using std::map;
using std::string;

#ifdef USE_GUARD

const scalarT eps = 1e-3;

namespace
{

const auto ZERO_EPS = "ZERO EPS";
const auto NN_ZERO_EPS = "NON NE ZERO EPS";

map<string, scalarT> extreme_values;

struct counter {
    counter() {}
    ~counter()
    {
        for (auto it : extreme_values) {
            printf("%s : %e\n", it.first.c_str(), it.second);
        }
    }
};

counter _worest;
} // namespace

void assert_unit(const vector3 &v, const string s, const string t)
{
    assert_unit(v, s + ":" + t);
}

void assert_unit(const vector3 &v, const string s)
{
    auto d = fabs(len(v) - 1);
    bool p = d < eps;
    if (not p) {
        fprintf(stderr, "failed to %s, diff %e, %s\n", __func__, d, s.c_str());
    }
    assert(p);
}

void assert_zero(scalarT z, const string s)
{
    scalarT v = fabs(z);
    if (v > extreme_values[ZERO_EPS])
        extreme_values[ZERO_EPS] = v;
    bool p = v < eps;
    if (not p) {
        fprintf(stderr, "failed to %s, value %e =! 0, %s\n", __func__, z,
                s.c_str());
    }
    assert(p);
}

void assert_non_negative_zero(scalarT z, const std::string s)
{
    bool p = 0 <= z && z < eps;
    if (z > extreme_values[NN_ZERO_EPS])
        extreme_values[NN_ZERO_EPS] = z;
    if (not p) {
        fprintf(stderr, "failed to %s at %s, value %e\n", __func__, s.c_str(),
                z);
    }
    assert(p);
}

#else

void assert_unit(const vector3 &, const string) {}
void assert_zero(scalarT, const string) {}
void assert_non_negative_zero(scalarT, const string) {}

#endif // #ifdef USE_GUARD
