#ifndef UTIL_H
#define UTIL_H

#include <string>

class Util
{
public:
    Util();
    static std::string getCurrentTimeCommand();
    static std::string getUptimeCommand();
    static std::string getPsCommand();
    static std::string getDateIn_YYYY_DD_MM();

};
#endif