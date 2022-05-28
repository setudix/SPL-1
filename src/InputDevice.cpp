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
#define INPUT_DEVICE_PATH "/dev/input/by-path/"

extern int start;
int cnt = 0;
int key_press_cnt[KEY_CODE_SIZE];
const char *keyboard_path;
const char *mouse_path;
namespace SPL
{
    void checkKeyboardButtonPress()
    {
        std::string temp_keyb_path = SPL::runCommand(SPL::Util::getKeyboardPath(), "r");
        keyboard_path = temp_keyb_path.c_str();
        int fd = open(keyboard_path, O_RDONLY);

        SPL::input keyboard;
        bool ignore_this_keypress = 0;
        while (1)
        {
            if (read(fd, &keyboard, sizeof keyboard))
            {
                if (keyboard.type == 1) // EV.KEY is 1
                {
                    if (ignore_this_keypress)
                    {
                        ignore_this_keypress = 0;
                        continue;
                    }
                    is_idle = 0;
                    InactivityStart.setTime(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));

                    key_press_cnt[keyboard.code]++;
                    ignore_this_keypress = 1;

                    // printf("%s = %d\n", key_codes[keyboard.code].c_str(), key_press_cnt[keyboard.code]);
                    fflush(stdin);
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }

    void checkMouseActivity()
    {
        std::string temp_mouse_path = SPL::runCommand(SPL::Util::getMousePath(), "r");
        mouse_path = temp_mouse_path.c_str();
        int fd = open(mouse_path, O_RDONLY);

        SPL::input mouse;
        while (1)
        {

            if (read(fd, &mouse, sizeof mouse))
            {
                if (mouse.type == 1 || mouse.type == 2)
                {
                    is_idle = 0;
                    start = clock();
                    InactivityStart.setTime(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }

    void countKeyPress()
    {
        while (keyboard_path == NULL)
        {
            puts("keyboard path not set. sleeping");
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        }
        int fd = open(keyboard_path, O_RDONLY);

        SPL::ActiveWindow activeWindow;
        std::string *activeWindowName = new std::string;
        SPL::input keyboard;
        bool ignore_this_keypress = 0;

        while (1)
        {
            if (read(fd, &keyboard, sizeof keyboard))
            {
                if (keyboard.type == 1) // EV.KEY is 1
                {
                    if (ignore_this_keypress)
                    {
                        ignore_this_keypress = 0;
                        continue;
                    }

                    ignore_this_keypress = 1;
                    root_BST->lock();
                        SPL::BST_Node *temp = root_BST->search(activeWindow.get_active_window_name());

                        if (temp != NULL)
                        {
                            temp->key_frequency[keyboard.code]++;
                            printf("process name : %s , %s = %d \n",activeWindow.get_active_window_name().c_str(), key_codes[keyboard.code].c_str(), temp->key_frequency[keyboard.code]);
                        }                
                    root_BST->unlock();
                }
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(5));
        }
    }
}