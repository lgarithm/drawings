#include <rey/base/params.h>

#include <cassert>

#include <rey/tracing/display.h>
#include <rey/model/model.h>
#include <rey/testing/testing.h>

void test_1()
{
    image_task cfg;
    static const char *argv[] = {"name", "-d", "wqxga"};
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
    static const char *argv2[] = {"", "-d", "10X10"};
    {
        bool f = parse(3, argv2, cfg);
        assert(f);
        assert(cfg.d.width == 10);
        assert(cfg.d.height == 10);
    }
}

void test_2()
{
    static const char *argv[] = {
        "name", "-m", "sphere(1,(1,1,0))", "-m", "sphere(1,(1,1,1))",
    };
    {
        image_task cfg;
        bool f = parse(3, argv, cfg);
        assert(f);
        assert(cfg.w.objects.size() == 1);
    }
    {
        image_task cfg;
        bool f = parse(4, argv, cfg);
        assert(not f);
    }
    {
        image_task cfg;
        bool f = parse(5, argv, cfg);
        assert(f);
        assert(cfg.w.objects.size() == 2);
    }
}

void test_3()
{
    static const char *argv[] = {
        "name", "-l", "light((0,0,0), (.5, .5, .5))",
    };
    {
        image_task cfg;
        bool f = parse(2, argv, cfg);
        assert(not f);
    }
    {
        image_task cfg;
        bool f = parse(3, argv, cfg);
        assert(f);
    }
}

void test_4()
{
    static const char *argv[] = {
        "", "-e", "0-100, 100-200",
    };
    {
        image_task cfg;
        bool f = parse(2, argv, cfg);
        assert(not f);
    }
    {
        image_task cfg;
        bool f = parse(3, argv, cfg);
        assert(f);
        assert(cfg.part);
        assert(size(cfg.c) == 10000);
    }
}

int main()
{
    test(1);
    test(2);
    test(3);
    test(4);
    return 0;
}
