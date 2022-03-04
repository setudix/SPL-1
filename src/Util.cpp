#include "../include/Util.h"

std::string Util::getCurrentTimeCommand()
{
    return "date +%F%r";
}

std::string Util::getUptimeCommand()
{
    return "uptime -s";
}

std::string Util::getPsCommand()
{
    return "ps -eo user,pid,ppid,lstart,comm";
}