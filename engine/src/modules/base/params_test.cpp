#include "params.h"

#include <cassert>

#include "model.h"
#include "testing.h"

void test_1()
{
  config cfg;
  static const char * argv[] = {"name", "-d", "wqxga"};
  {
    bool f = parse(2, argv, cfg);
    assert(not f);
    assert(cfg.d.width == 1024);
  }
  {
    bool f = parse(3, argv, cfg);
    assert(f);
    assert(cfg.d.width == 2560);
  }
  static const char * argv2[] = {"", "-d", "10X10"};
  {
    bool f = parse(3, argv2, cfg);
    assert(f);
    assert(cfg.d.width == 10);
    assert(cfg.d.height == 10);
  }
}

object* parse_model(const char * str);

void test_2()
{
  static const char * succ[] = {
    "sphere(1,(1,1,1))",
    "sphere(1, (1, 1, 1))",
    //"sphere (1, (1, 1, 1))",
  };
  for (auto it : succ) { assert(parse_model(it)); }
}

void test_3()
{
  static const char * fail[] = {
    "sphere(1)",
    "sphere (1, (1, 1, 1))",
  };
  for (auto it : fail) { assert(parse_model(it) == nullptr); }
}

void test_4()
{
  static const char * argv[] = {
    "name",
    "-m", "sphere(1,(1,1,0))",
    "-m", "sphere(1,(1,1,1))",
  };
  {
    config cfg;
    bool f = parse(3, argv, cfg);
    assert(f);
    assert(cfg.oo.size() == 1);
  }
  {
    config cfg;
    bool f = parse(4, argv, cfg);
    assert(not f);
  }
  {
    config cfg;
    bool f = parse(5, argv, cfg);
    assert(f);
    assert(cfg.oo.size() == 2);
  }
}

void test_5()
{
  static const char * argv[] = {
    "name",
    "-l", "light((0,0,0), (.5, .5, .5))",
  };
  {
    config cfg;
    bool f = parse(2, argv, cfg);
    assert(not f);
  }
  {
    config cfg;
    bool f = parse(3, argv, cfg);
    assert(f);
  }
}

int main()
{
  test(1);
  test(2);
  test(3);
  test(4);
  test(5);
  return 0;
}
