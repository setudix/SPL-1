#include "../include/Process.h"
#include <cstdio>
#define TMPSIZE 64

Process::Process(std::string str)
{
    setProcess(str);
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
    printf("%-7s %-10d %-10d %20s %40s\n", user.c_str(),
           pid, ppid, lstart.c_str(), comm.c_str());
}

void Process::displayProcess(std::vector<Process> &proc)
{
    for (auto i : proc)
    {
        i.displayProcess();
    }
}

Time Process::getTime()
{
    return start_time;
}