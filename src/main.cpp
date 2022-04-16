#ifndef __linux__
#error
#endif
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>

#include "../include/mystring.h"
#include "../include/Time.h"
#include "../include/commands.h"
#include "../include/idletime.h"
#include "../include/InputDevice.h"
#include "../include/Util.h"
#include "../include/Process.h"
#include "../include/bst.h"
#include "../include/myvector.h"
#include "../include/mysort.h"
#include "../include/process_management.h"

int main()
{
    std::string uptime = runCommand(Util::getUptimeCommand(), "r");
    std::string current_time = runCommand(Util::getCurrentTimeCommand(), "r");

    std::thread keyboard_thread(checkKeyboardButtonPress);
    std::thread mouse_thread(checkMouseActivity);
    std::thread idle_time_thread(elapsedTime);
    std::thread process_management_thread(checkProcess);

    keyboard_thread.join();
    mouse_thread.join();
    idle_time_thread.join();
    process_management_thread.join();

    return 0;
}
