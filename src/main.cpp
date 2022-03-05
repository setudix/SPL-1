#ifndef __linux__
#error
#endif
#include <iostream>
#include <string>
#include <thread>

#include "../include/mystring.h"
#include "../include/Time.h"
#include "../include/commands.h"
#include "../include/idletime.h"
#include "../include/InputDevice.h"
#include "../include/Util.h"
#include "../include/Process.h"

int main()
{
    std::string uptime = runCommand(Util::getUptimeCommand(), "r");
    std::string current_time = runCommand(Util::getCurrentTimeCommand(), "r");

    // printf("uptime -- %s\ncurrent time -- %s\n", uptime.c_str(), current_time.c_str());
    //  printf("ascii vale at back of uptime = %d\n", (int)uptime.back());

    // Time t1(uptime);
    // Time t2(current_time);

    // t1.displayTime();
    // t2.displayTime();

    // Time t3 = t1 + t2;
    // t3.displayTime();
    // t3 = t1 - t2;
    // t3.displayTime();

    // runThreads();

    std::vector<Process> proc;
    runCommand(Util::getPsCommand(), "r", proc);
    Process::displayProcess(proc);

    Process::sortProcess(proc);
    puts("-----------------");
    // Time ct = runCommand(Util::getCurrentTimeCommand(), "r");
    // for (auto x : proc)
    // {
    //     x.displayProcess();
    //     Time t = x.getRunningFor(current_time);
    //     printf(" running for ");
    //     t.displayTime();
    //     puts("");
    // }

    std::vector<Process> unique_proc;
    unique_proc = getUniqueProcessForUser(proc, runCommand("whoami", "r"));
    Process::sortProcessByActiveTime(unique_proc);
    for (auto x : unique_proc)
    {
        x.displayProcessWithActiveTime();
        puts("");
    }
    return 0;
}
