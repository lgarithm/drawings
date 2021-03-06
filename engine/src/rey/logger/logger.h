#pragma once


#include <string>

struct with_c {
    with_c(unsigned short, unsigned short);
    ~with_c();
};

struct clogger {
    static const int RED;
    static const int GREEN;

    int bg;
    int color;

    clogger();
    void log(const std::string, int, int);
    void log(const std::string, int);
    void log(const std::string);
};

struct slogger {
    const std::string name;
    clogger lo;

    slogger(const std::string);
    ~slogger();
};


