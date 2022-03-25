#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <cstdio>
#include <vector>

#include "Time.h"

class Process
{
private:
    std::string user;
    int pid;
    int ppid;
    std::string lstart;
    std::string comm;
    std::string getMonth(std::string month);
    std::string getDay(int day);
    Time start_time;
    Time active_time;

public:
    Process();
    Process(std::string str, Time current_time);
    Process(std::string str);
    void setProcess(std::string str);
    static void displayProcess(std::vector<Process> &proc);
    void displayProcess();
    Time getTime() const;
    void setTime(Time a);
    std::string getUser();
    Time getTimeNonConstant();
    std::string getProcessName() const;
    Time getRunningFor(Time a);
    Time getActiveTime() const;
    static void sortProcess(std::vector<Process> &proc);
    static void sortProcessByActiveTime(std::vector<Process> &proc);
    void displayProcessWithActiveTime();
    void killProcess();
};

std::vector<Process> getUniqueProcessForUser(std::vector<Process> &proc, std::string user);

bool operator==(const Process &a, const Process &b);
bool operator<(const Process &a, const Process &b);
bool operator>(const Process &a, const Process &b);
#endif