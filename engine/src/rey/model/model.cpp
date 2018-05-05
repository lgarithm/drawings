#include <rey/model/model.h>

#include <memory>

#include <rey/base/maybe.h>
#include <rey/linear/point.h>

using std::unique_ptr;

std::optional<intersection> complex_object::intersect(const ray &r) const
{
    auto t = meet(r);
    if (t.has_value()) {
        return just(intersection{this, t.value()});
    }
    return nothing<intersection>();
}

void operator+=(world &w, object *po)
{
    w.objects.push_back(unique_ptr<object>(po));
}
