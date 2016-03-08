#ifndef PROFILE_H
#define PROFILE_H

#include "model.h"

struct trace_logger{};
struct scope_logger{};

void log_trace(const ray&, int dep);

#endif  // PROFILE_H
