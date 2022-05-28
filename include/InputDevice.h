#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

#include "process_management.h"
#include "active_window.h"

namespace SPL
{
    struct input
    {
        __time_t tv_sec;       // long
        __suseconds_t tv_usec; // long
        unsigned short type;
        unsigned short code;
        signed int value;
    };
    void setKeyboardPath();
    void setMousePath();
    void checkIdleTime();
    void checkKeyboardButtonPress();
    void checkMouseActivity();
    void countKeyPress();
}
extern bool is_idle;
extern SPL::BST* root_BST;

#endif