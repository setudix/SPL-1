#ifndef PROCESS_H
#define PROCESS_H

#include <string>
#include <cstdio>
#include <vector>

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
    void displayProcess();
public:
    Process();
    Process(std::string str);
    void setProcess(std::string str);
    static void displayProcess(std::vector <Process> &proc);


};
#endif