#include "../include/Util.h"

std::string SPL::Util::getCurrentTimeCommand()
{
    return "date +%F\" \"%X";
}

std::string SPL::Util::getUptimeCommand()
{
    return "uptime -s";
}

std::string SPL::Util::getPsCommand()
{
    return "ps -eo user,pid,ppid,lstart,comm";
}
std::string SPL::Util::getDateIn_YYYY_DD_MM()
{
    return "date +%F";
}
std::string SPL::Util::getKeyboardPath()
{
    return "echo /dev/input/by-path/*event-kbd";
}

std::string SPL::Util::getMousePath()
{
    return "echo /dev/input/by-path/*event-mouse";
}

std::string SPL::Util::getPwdCommand()
{
    return "pwd";
}
std::string SPL::Util::getKillCommand()
{
    return "kill";
}