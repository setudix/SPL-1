#include "../include/Process.h"
#include <cstdio>
#include <algorithm>
#include "../include/mysort.h"

#define TMPSIZE 64

SPL::Process::Process()
{
}
SPL::Process::Process(std::string str)
{
    setProcess(str);
}
SPL::Process::Process(std::string str, Time current_time)
{
    setProcess(str);
    last_active = current_time;
}
void SPL::Process::setProcess(std::string str)
{
    char temp_user[TMPSIZE];
    char temp_month_name[TMPSIZE];
    char temp_time[TMPSIZE];
    char temp_year[TMPSIZE];
    char temp_comm[TMPSIZE];
    int temp_date;

    sscanf(str.c_str(), "%s %d %d %*s %s %d %s %s %s",
           temp_user, &pid, &ppid, temp_month_name,
           &temp_date, temp_time, temp_year, temp_comm);

    user = temp_user;
    comm = temp_comm;
    lstart = (std::string)temp_year + '-' + getMonth((std::string)temp_month_name) + '-' + getDay(temp_date) + ' ' + temp_time;
    start_time.setTime(lstart);
    hasBeenClosed = 0;
}

std::string SPL::Process::getMonth(std::string month)
{
    if (month == "Jan")
        return "01";
    if (month == "Feb")
        return "02";
    if (month == "Mar")
        return "03";
    if (month == "Apr")
        return "04";
    if (month == "May")
        return "05";
    if (month == "Jun")
        return "06";
    if (month == "Jul")
        return "07";
    if (month == "Aug")
        return "08";
    if (month == "Sep")
        return "09";
    if (month == "Oct")
        return "10";
    if (month == "Nov")
        return "11";
    // if (month == "Dec")
    return "12";
}

std::string SPL::Process::getDay(int day)
{
    if (!(day / 10))
        return '0' + std::to_string(day);
    else
        return std::to_string(day);
}

void SPL::Process::displayProcess()
{
    printf("%-7s %-10d %-10d %20s %40s", user.c_str(),
           pid, ppid, lstart.c_str(), comm.c_str());
}

void SPL::Process::displayProcess(SPL::MyVector<SPL::Process> &proc)
{
    for (auto i : proc)
    {
        i.displayProcess();
        puts("");
    }
}

std::string SPL::Process::getProcessName() const
{
    return comm;
}
SPL::Time SPL::Process::getTime() const
{
    return start_time;
}

void SPL::Process::setTime(SPL::Time a)
{
    start_time = a;
}
std::string SPL::Process::getUser()
{
    return user;
}
SPL::Time SPL::Process::getTime()
{
    return start_time;
}
SPL::Time SPL::Process::getRunningFor(SPL::Time a)
{
    return a - start_time;
}
SPL::Time SPL::Process::getActiveTime()
{
    active_time = last_active - start_time;
    return active_time;
}
void SPL::Process::sortProcess(SPL::MyVector<SPL::Process> &proc)
{
    SPL::quicksort<SPL::Process>(proc,[](SPL::Process &a, SPL::Process &b)
    {
        return a <= b;
    });
}

std::vector<SPL::Process> getUniqueProcessForUser(std::vector<SPL::Process> &proc, std::string user)
{
    std::vector<SPL::Process> a;
    a.push_back({proc[0]});
    for (auto x : proc)
    {
        if (x.getUser() == user)
        {
            SPL::Process temp = a.back();

            if (temp.getProcessName() == x.getProcessName())
                if (x.getTime() < temp.getTime())
                    temp.setTime(x.getTime());
            else
                a.push_back({x});
        }
    }
    return a;
}

void SPL::Process::sortProcessByActiveTime(SPL::MyVector<SPL::Process> &proc)
{
    quicksort<SPL::Process>(proc,[](SPL::Process &a, SPL::Process &b){
        return a >= b;
    });
}

void SPL::Process::displayProcessWithActiveTime()
{
    displayProcess();
    printf(" Active for : ");
    getActiveTime().displayTime();
}

void SPL::Process::killProcess()
{
    // not final
    std::string command = "kill " + std::to_string(pid);
    system((const char *)command.c_str());
}
bool SPL::Process::getHasBeenClosed()
{
    return hasBeenClosed;
}

void SPL::Process::setHasBeenClosed(bool x)
{
    hasBeenClosed = x;
}
bool operator==(const SPL::Process &a, const SPL::Process &b)
{
    if (a.getProcessName() == b.getProcessName())
        return a.getTime() == b.getTime();

    return 0;
}
bool operator<(const SPL::Process &a, const SPL::Process &b)
{
    if (a.getProcessName() == b.getProcessName())
        return a.getTime() < b.getTime();

    return a.getProcessName() < b.getProcessName();
}

bool operator>(const SPL::Process &a, const SPL::Process &b)
{
    return !(a < b);
}

bool operator<=(const SPL::Process &a, const SPL::Process &b)
{
    if (a.getProcessName() == b.getProcessName())
        return a.getTime() <= b.getTime();

    return a.getProcessName() <= b.getProcessName();

}

bool operator!=(const SPL::Process &a, const SPL::Process &b)
{
    if (a.getProcessName() == b.getProcessName())
        return a.getTime() != b.getTime();

    return 1;
}

bool operator>=(const SPL::Process &a, const SPL::Process &b)
{
    if (a.getProcessName() == b.getProcessName())
        return a.getTime() >= b.getTime();

    return a.getProcessName() >= b.getProcessName();
}
void SPL::Process::setLastActiveTime(SPL::Time last_active)
{
    this->last_active = last_active;
}

SPL::Time SPL::Process::getLastActiveTime()
{
    return last_active;
}

SPL::Process& SPL::Process::operator=(const SPL::Process &x)
{
    this->user = x.user;
    this->pid = x.pid;
    this->ppid = x.pid;
    this->lstart = x.lstart;
    this->comm = x.comm;
    this->start_time = x.start_time;
    this->active_time = x.active_time;
    this->last_active = x.last_active;
    this->hasBeenClosed = x.hasBeenClosed;

    return *this;
}
int SPL::Process::getPid()
{
    return pid;
}

int SPL::Process::getPpid()
{
    return ppid;
}