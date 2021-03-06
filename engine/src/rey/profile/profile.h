#pragma once


#include <map>
#include <string>

#include <rey/model/model.h>

struct trace_logger {
};

struct scope_logger {
    const std::string k;

    scope_logger(const std::string k);
    ~scope_logger();

    static std::map<std::string, int> depth;
};

void log_trace(const ray &, int dep);


