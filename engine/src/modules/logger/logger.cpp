#include "logger.h"

#include <cstdio>

#include <string>

using std::string;

clogger::clogger() : bg(0), color(GREEN) {}

void clogger::log(const string msg, int c, int b)
{ printf("\e[%d;%dm%s\e[m\n", b, c, msg.c_str()); }

void clogger::log(const string msg, int c)
{ log(msg, c, bg); }

void clogger::log(const string msg)
{ log(msg, color, bg); }

slogger::slogger(const string name) : name(name) { lo.log("BEGIN " + name); }
slogger::~slogger() { lo.log("END " + name); }

const int clogger::RED = 31;
const int clogger::GREEN = 32;
