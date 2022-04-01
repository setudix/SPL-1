#include <cstdio>
#include <thread>
#include <time.h>
#include <mutex>

#include "../include/Time.h"
#include "../include/commands.h"
#include "../include/Util.h"

// setting the idle time
#define IDLETIME 5

#define IDLETIME_LOG_PATH "../logs/total_idletime.txt"

bool is_idle = 0;
int start;
int idle_time_start;

Time InactivityStart;
#define TEST 1

void setStartTime()
{
    InactivityStart.setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
}
#ifdef TEST

void getIdleTime(Time IdleTimeStart, Time &IdleTime)
{
    Time *ct = new Time;

    while (is_idle)
    {
        ct->setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
        IdleTime = *ct - IdleTimeStart;
    }
    delete ct;
}

void elapsedTime()
{
    while (1)
    {
        Time ct(runCommand(Util::getCurrentTimeCommand(), "r"));
        Time diff = ct - InactivityStart;
        if (diff.getTimeInSeconds() > IDLETIME)
        {
            printf("IDLE\n");
            Time IdleTimeStart(runCommand(Util::getCurrentTimeCommand(), "r"));
            is_idle = 1;
            Time *IdleTime = new Time;
            getIdleTime(IdleTimeStart, *IdleTime);

            if (IdleTime->getTimeInSeconds() > 0)
            {
                printf("Idle for :");
                IdleTime->displayTime();
                puts("");
            }
            delete IdleTime;
        }
    }
}

// void write_idletime(Time &IdleTime)
// {
//     FILE *idletime_file = fopen
// }

#endif

#ifndef TEST

double getIdleTime()
{
    double idle_time = -1.0;
    while (is_idle)
    {
        idle_time = (double)(clock() - idle_time_start) / CLOCKS_PER_SEC;
    }
    return idle_time;
}
void elapsedTime()
{
    while (1)
    {
        double tmp_time = (double)(clock() - start) / CLOCKS_PER_SEC;

        if (tmp_time > IDLETIME)
        {
            printf("IDLE!!\n");
            idle_time_start = clock();
            is_idle = 1;
            double f = getIdleTime();
            // fflush(stdout);
            if (f >= 0.0)
            {
                printf("idle for -- %lf\n", f);
            }
            start = clock();
        }
    }
}
#endif