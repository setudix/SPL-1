#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
    Util();
    static std::string getCurrentTimeCommand();
    static std::string getUptimeCommand();
};
#endif