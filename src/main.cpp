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

int main()
{
    std::string uptime = runCommand("uptime -s", "r");
    std::string current_time = runCommand("date +%F%r", "r");

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

    runThreads();
    // std::thread keyboard_thread(checkKeyboardButtonPress);
    // std::thread mouse_thread(checkMouseActivity);
    // std::thread idle_time_thread(elapsedTime);

    // keyboard_thread.join();
    // mouse_thread.join();
    // idle_time_thread.join();

    // std::thread ff(f);
    // ff.join();

    return 0;
}
