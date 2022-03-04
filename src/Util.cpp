#include "../include/Util.h"

std::string Util::getCurrentTimeCommand(){
    return "date +%F%r";
}

std::string Util::getUptimeCommand(){
    return "uptime -s";
}