#include <rey/profile/profile.h>

#include <cstdio>

#include <map>
#include <string>

#include <rey/model/model.h>

void log_trace(const ray &r, int dep)
{
    printf("%d-th tracing ray{%s + %st}\n", dep, p_str(r.origin),
           p_str(r.direction));
}

std::map<std::string, int> scope_logger::depth;

scope_logger::scope_logger(const std::string k) : k(k) { ++depth[k]; }

scope_logger::~scope_logger() { --depth[k]; }
