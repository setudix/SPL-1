#include "../include/Util.h"

std::string Util::getCurrentTimeCommand()
{
    return "date +%F\" \"%X";
}

std::string Util::getUptimeCommand()
{
    return "uptime -s";
}

std::string Util::getPsCommand()
{
    return "ps -eo user,pid,ppid,lstart,comm";
}
std::string Util::getDateIn_YYYY_DD_MM()
{
    return "date +%F";
}
std::string Util::getKeyboardPath()
{
    return "echo /dev/input/by-path/*event-kbd";
}

std::string Util::getMousePath()
{
    return "echo /dev/input/by-path/*event-mouse";
}
