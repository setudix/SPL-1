#include <cstdio>
#include <thread>
#include <time.h>
#include <mutex>
#include <fstream>

#include "../include/Time.h"
#include "../include/commands.h"
#include "../include/Util.h"

// setting the idle time
#define IDLETIME 5

#define IDLETIME_DIR_PATH "../logs/idletime/"

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

void getIdleTime(Time &IdleTimeStart, Time &IdleTime)
{
    Time *ct = new Time;

    while (is_idle)
    {
        ct->setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
        IdleTime = *ct - IdleTimeStart;
    }
    delete ct;
}
void write_idletime(Time &IdleTime)
{
    std::fstream file;
    std::string filename =  runCommand("pwd", "r") + "/logs/idletime/" + runCommand(Util::getDateIn_YYYY_DD_MM(),"r") + ".dat";
    // std::string filename = runCommand("pwd","r");
    // filename += "/logs/idletime/f.txt";

    printf("%s\n",filename.c_str());

    file.open(filename, std::ios::in);

    if (file.is_open())
    {
        long long time;
        file >> time;
        
        time += IdleTime.getTimeInSeconds();
        file.close();
        file.open(filename, std::ios::out);
        file << time;

        file.close(); 
    }
    else 
    {
        std::fstream newfile;
        newfile.open(filename, std::ios::out);
        if (!newfile.is_open())
            puts("new file is not created");
        newfile << IdleTime.getTimeInSeconds();
        newfile.close();
    }

}

void elapsedTime()
{
    Time ct;
    Time diff;
    while (1)
    {
        ct.setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
        diff = ct - InactivityStart;
        if (diff.getTimeInSeconds() > IDLETIME)
        {
            printf("IDLE\n");
            Time *IdleTimeStart = new Time;
            Time *IdleTime = new Time;
            IdleTimeStart->setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
            is_idle = 1;

            getIdleTime(*IdleTimeStart, *IdleTime);

            if (IdleTime->getTimeInSeconds() > 0)
            {
                printf("Idle for :");
                IdleTime->displayTime();
                puts("");
                // // write_idletime(*IdleTime);
            }
            delete IdleTime;
            delete IdleTimeStart;
        }
    }
}


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