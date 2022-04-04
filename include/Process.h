#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <cstdio>
#include <vector>
#include "myvector.h"
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
    Time last_active;
    bool hasBeenClosed;

public:
    Process();
    Process(std::string str, Time current_time);
    Process(std::string str);
    void setProcess(std::string str);
    static void displayProcess(MyVector<Process> &proc);
    void displayProcess();
    Time getTime() const;
    void setTime(Time a);
    std::string getUser();
    Time getTime();
    std::string getProcessName() const;
    Time getRunningFor(Time a);
    Time getActiveTime();
    static void sortProcess(MyVector<Process> &proc);
    static void sortProcessByActiveTime(MyVector<Process> &proc);
    void displayProcessWithActiveTime();
    void killProcess();
    bool getHasBeenClosed();
    void setHasBeenClosed(bool x);
    void setLastActiveTime(Time a);
    Time getLastActiveTime();

};

std::vector<Process> getUniqueProcessForUser(std::vector<Process> &proc, std::string user);

bool operator==(const Process &a, const Process &b);
bool operator<(const Process &a, const Process &b);
bool operator>(const Process &a, const Process &b);
bool operator<=(const Process &a, const Process &b);
bool operator!=(const Process &a, const Process &b);
bool operator>=(const Process &a, const Process &b);

#endif