#include <iostream>
#include <thread>
#include <cstdlib>
#include <cstdio>
#include <fcntl.h>
#include <unistd.h>
#include <linux/input.h>
#include <sys/stat.h>
#include <time.h>
#include <pthread.h>
#include <thread>
#include <chrono>

#include "../include/InputDevice.h"
#include "../include/idletime.h"
#include "../include/Time.h"
#include "../include/Util.h"
#include "../include/commands.h"
#include "../include/keycodes.h"

// keyboard and mouse driver locations
#define KEYBOARD_PATH "/dev/input/by-path/pci-0000:00:1d.0-usb-0:1.5:1.0-event-kbd"
#define MOUSE_PATH "/dev/input/by-path/pci-0000:00:1d.0-usb-0:1.6:1.0-event-mouse"

extern int start;
int cnt = 0;
int key_press_cnt[KEY_CODE_SIZE];

void checkKeyboardButtonPress()
{
    input keyboard;
    int fd = open(KEYBOARD_PATH, O_RDONLY);
    while (1)
    {
        if (read(fd, &keyboard, sizeof keyboard))
        {
            if (keyboard.type == 1) // EV.KEY is 1
            {
                is_idle = 0;
                start = clock();
                InactivityStart.setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
                // fflush(stdout);
                // printf("%d.Key press!\n", ++cnt);
                key_press_cnt[keyboard.code]++;

                printf("%s = %d\n", key_codes[keyboard.code].c_str(), key_press_cnt[keyboard.code]);
                fflush(stdin);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void checkMouseActivity()
{
    input mouse;
    int fd = open(MOUSE_PATH, O_RDONLY);
    while (1)
    {
        if (read(fd, &mouse, sizeof mouse))
        {
            if (mouse.type == 1 || mouse.type == 2)
            {
                is_idle = 0;
                start = clock();
                InactivityStart.setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
                // fflush(stdout);
                // printf("%d.Mouse Activity!\n", ++cnt);
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}

void runThreads()
{
    std::thread keyboard_thread(checkKeyboardButtonPress);
    std::thread mouse_thread(checkMouseActivity);
    std::thread idle_time_thread(elapsedTime);

    // keyboard_thread.detach();
    // mouse_thread.detach();
    // idle_time_thread.detach();

    keyboard_thread.join();
    mouse_thread.join();
    idle_time_thread.join();
}