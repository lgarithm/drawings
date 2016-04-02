#include "constants.h"

#include <map>
#include <string>

#include "view.h"

using std::map;
using std::string;

map<string, camera> build_cameras(scalarT d)
{
  map<string, camera> cs;
  cs["top"] = camera::top(d);
  cs["bottom"] = camera::bottom(d);
  cs["front"] = camera::front(d);
  cs["back"] = camera::back(d);
  cs["left"] = camera::left(d);
  cs["right"] = camera::right(d);
  return cs;
}
