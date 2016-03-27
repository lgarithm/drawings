#include "prog.h"

#include <regex>
#include <sstream>
#include <string>

#include "color.h"
#include "maybe.h"
#include "material.h"
#include "model.h"
#include "model-builtin.h"
#include "parse.h"

using std::istream;
using std::regex_search;
using std::smatch;
using std::string;
using std::istringstream;


std::regex regex(const string& str)
{
  try{
    return std::regex(str);
  }
  catch (const std::regex_error& e) {
    printf("%s caught: %s\n", e.what(), str.c_str());
    throw e;
  }
}

maybe<color> p_color(const string& str)
{
  {
    auto it = colors.find(str);
    if (it != colors.end()) {
      return just(it->second);
    }
  }
  {
    istringstream ss(str);
    color c;
    if (ss >> c) {
      static const auto f = [](colorT x){ return 0 <= x && x <= 1; };
      if (f(c.r) && f(c.g) && f(c.b)) {
        return just(c);
      }
    }
  }
  return nothing<color>();
}

maybe<material> p_material(const string& str)
{
  static const auto pc = string("\\(\\s*([^)]+)\\s*\\)");
  material mt;
  {
    static const auto p = regex("dc" + pc);
    smatch m;
    if (regex_search(str, m, p)) {
      auto c = p_color(m[1].str());
      if (c.just) {
        mt.diffuse = c.it;
      }
    }
  }
  {
    static const auto p = regex("sc" + pc);
    smatch m;
    if (regex_search(str, m, p)) {
      auto c = p_color(m[1].str());
      if (c.just) {
        mt.specular = c.it;
      }
    }
  }
  {
    smatch m;
    if (regex_search(str, m, regex("rf=([0-9\\.]+)"))) {
      colorT rf;
      if (sscanf(m[1].str().c_str(), "%lf", &rf) == 1 && 0 <= rf && rf <= 1) {
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

object* p_builtin_model(const string& str)
{
  static const auto p = regex("([a-z0-9]+)\\((.+)\\)");
  smatch m;
  if (regex_search(str, m, p)) {
    const string name = m[1].str();
    istringstream ss(m[2].str());
    if (name == "floor" ) {
      return new Chessboard;
    }
  }
  return nullptr;
}

simple_object* p_s_model(const string& str)
{
  static const auto p = regex("([a-z0-9]+)\\((.+)\\)");
  smatch m;
  if (regex_search(str, m, p)) {
    const string name = m[1].str();
    istringstream ss(m[2].str());
    if (name == "sphere" ) {
      double s;
      point3 p;
      if (ss >> s >> comma >> lb >> p >> rb) {
        if (s > 0) {
          return new sphere(s, p);
        }
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

object* p_model_regex_unsafe(const string& str)
{
  static const auto p = regex("([^@]+)(@(.+))?");
  smatch m;
  if (regex_search(str, m, p)) {
    material mt;
    if (m.size() == 4) {
      auto mmt = p_material(m[3].str());
      if (mmt.just) mt = mmt.it;
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
  if (str == "floor") {
    return new Chessboard;
  }
  return nullptr;
}

object* p_model(const string& str)
{
  try {
    return p_model_regex_unsafe(str);
  }
  catch (const std::regex_error& e) {
    printf("regex_error caught: %s\n", e.what());
  }
  return nullptr;
}
