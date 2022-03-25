#include "../include/Process.h"
#include <cstdio>
#include <algorithm>
#define TMPSIZE 64

Process::Process()
{
}
Process::Process(std::string str)
{
    setProcess(str);
}
Process::Process(std::string str, Time current_time)
{
    setProcess(str);
    active_time = start_time - current_time;
}
void Process::setProcess(std::string str)
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
}

std::string Process::getMonth(std::string month)
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

std::string Process::getDay(int day)
{
    if (!(day / 10))
    {
        return '0' + std::to_string(day);
    }
    else
    {
        return std::to_string(day);
    }
}

void Process::displayProcess()
{
    printf("%-7s %-10d %-10d %20s %40s", user.c_str(),
           pid, ppid, lstart.c_str(), comm.c_str());
}

void Process::displayProcess(std::vector<Process> &proc)
{
    for (auto i : proc)
    {
        i.displayProcess();
        puts("");
    }
}

std::string Process::getProcessName() const
{
    return comm;
}
Time Process::getTime() const
{
    return start_time;
}

void Process::setTime(Time a)
{
    start_time = a;
}
std::string Process::getUser()
{
    return user;
}
Time Process::getTimeNonConstant()
{
    return start_time;
}
Time Process::getRunningFor(Time a)
{
    return a - start_time;
}
Time Process::getActiveTime() const
{
    return active_time;
}
void Process::sortProcess(std::vector<Process> &proc)
{
    std::sort(proc.begin(), proc.end(), [](const Process &a, const Process &b)
              { return a < b; });
}

std::vector<Process> getUniqueProcessForUser(std::vector<Process> &proc, std::string user)
{
    std::vector<Process> a;
    a.push_back({proc[0]});
    for (auto x : proc)
    {
        if (x.getUser() == user)
        {
            Process temp = a.back();

            if (temp.getProcessName() == x.getProcessName())
            {
                if (x.getTime() < temp.getTime())
                {
                    temp.setTime(x.getTime());
                }
            }
            else
            {
                a.push_back({x});
            }
        }
    }
    return a;
}

void Process::sortProcessByActiveTime(std::vector<Process> &proc)
{
    sort(proc.begin(), proc.end(), [](const Process &a, const Process &b)
         { return !(a.getActiveTime() < b.getActiveTime()); });
}

void Process::displayProcessWithActiveTime()
{
    displayProcess();
    printf(" Running for : ");
    getActiveTime().displayTime();
}

void Process::killProcess()
{
    // not final
    std::string command = "kill " + std::to_string(pid);
    system((const char *)command.c_str());
}
bool operator==(const Process &a, const Process &b)
{
    if (a.getProcessName() == b.getProcessName())
    {
        return a.getTime() == b.getTime();
    }

    return 0;
}
bool operator<(const Process &a, const Process &b)
{
    if (a.getProcessName() == b.getProcessName())
    {
        return a.getTime() < b.getTime();
    }

    return a.getProcessName() < b.getProcessName();
}

bool operator>(const Process &a, const Process &b)
{
    return !(a < b);
}