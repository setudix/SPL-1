#ifndef UTIL_H
#define UTIL_H

#include <string>
namespace SPL
{
    class Util
    {
    public:
        Util();
        static std::string getCurrentTimeCommand();
        static std::string getUptimeCommand();
        static std::string getPsCommand();
        static std::string getDateIn_YYYY_DD_MM();
        static std::string getKeyboardPath();
        static std::string getMousePath();
        static std::string getPwdCommand();
        static std::string getKillCommand();
    };
}
#endif