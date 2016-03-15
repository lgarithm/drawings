#include "r2d2_model.h"

#include <map>
#include <string>

#include "model.h"
#include "rey.h"

using std::map;
using std::string;

world* default_test_scene()
{
  auto w = new world;
  *w += new Chessboard(3);
  return w;
}

map<string, world_gen> examples()
{
  map<string, world_gen> mp;
  return mp;
}
