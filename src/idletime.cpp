#include <cstdio>
#include <thread>
#include <time.h>
#include <mutex>
#include <fstream>

#include "../include/Time.h"
#include "../include/commands.h"
#include "../include/Util.h"
#include "../include/idletime.h"

// setting the idle time
#define IDLETIME 5

#define IDLETIME_DIR_PATH "../logs/idletime/"

bool is_idle = 0;
int start;
int idle_time_start;

SPL::Time InactivityStart;

void setStartTime()
{
    InactivityStart.setTime(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));
}

void getIdleTime(SPL::Time &IdleTimeStart, SPL::Time &IdleTime)
{
    SPL::Time *ct = new SPL::Time;

    while (is_idle)
    {
        ct->setTime(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));
        IdleTime = *ct - IdleTimeStart;
    }
    delete ct;
}
void write_idletime(SPL::Time &IdleTime)
{
    std::fstream file;
    std::string filename =  SPL::runCommand("pwd", "r") + "/logs/idletime/" + SPL::runCommand(SPL::Util::getDateIn_YYYY_DD_MM(),"r") + ".dat";
    // std::string filename = runCommand("pwd","r");
    // filename += "/logs/idletime/f.txt";

    // printf("%s\n",filename.c_str());

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
namespace SPL
{
    void elapsedTime()
    {
        SPL::Time ct;
        SPL::Time diff;
        while (1)
        {
            ct.setTime(runCommand(Util::getCurrentTimeCommand(), "r"));
            diff = ct - InactivityStart;
            if (diff.getTimeInSeconds() > IDLETIME)
            {
                printf("IDLE\n");
                SPL::Time *IdleTimeStart = new SPL::Time;
                SPL::Time *IdleTime = new SPL::Time;
                IdleTimeStart->setTime(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));
                is_idle = 1;

                getIdleTime(*IdleTimeStart, *IdleTime);

                if (IdleTime->getTimeInSeconds() > 0)
                {
                    printf("Idle for :");
                    IdleTime->displayTime();
                    puts("");
                    write_idletime(*IdleTime);
                }
                delete IdleTime;
                delete IdleTimeStart;
            }
        }
    }
}
