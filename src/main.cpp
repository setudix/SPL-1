#ifndef __linux__
#error 
#endif
#include <iostream>
#include <string>

#include "../include/mystring.h"
#include "../include/Time.h"
#include "../include/commands.h"

int main()
{
    std::string uptime = runCommand("uptime -s", "r");
    std::string current_time = runCommand("date +%F%r", "r");

    printf("uptime -- %s\ncurrent time -- %s\n", uptime.c_str(), current_time.c_str());
    // printf("ascii vale at back of uptime = %d\n",(int)uptime.back());
    return 0;
}
