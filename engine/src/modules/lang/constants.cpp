#include "constants.h"

#include <map>
#include <string>

#include "view.h"

using std::map;
using std::string;

map<string, camera> build_cameras(scalarT d)
{
    map<string, camera> cs;
    cs["top"] = top(d);
    cs["bottom"] = bottom(d);
    cs["front"] = front(d);
    cs["back"] = back(d);
    cs["left"] = left(d);
    cs["right"] = right(d);
    return cs;
}
