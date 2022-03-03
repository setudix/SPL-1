#ifndef INPUTDEVICE_H
#define INPUTDEVICE_H

struct input
{
    __time_t tv_sec;       // long
    __suseconds_t tv_usec; // long
    unsigned short type;
    unsigned short code;
    signed int value;
};

void checkIdleTime();
void runThreads();

#endif