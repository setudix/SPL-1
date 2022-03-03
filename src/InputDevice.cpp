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
#include "../include/InputDevice.h"
#include "../include/idletime.h"

// keyboard and mouse driver locations
#define KEYBOARD_PATH "/dev/input/by-path/pci-0000:00:1d.0-usb-0:1.5:1.0-event-kbd"
#define MOUSE_PATH "/dev/input/by-path/pci-0000:00:1d.0-usb-0:1.6:1.0-event-mouse"

bool is_idle = 0;
extern int start;
int cnt = 0;
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
                // fflush(stdout);
                // printf("%d.Key press!\n", ++cnt);
            }
        }
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
                // fflush(stdout);
                // printf("%d.Mouse Activity!\n", ++cnt);
            }
        }
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