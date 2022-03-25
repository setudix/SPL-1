#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>

#include "../include/commands.h"
#include "../include/mystring.h"

#define BUFFER_SIZE 256
#define STR_SIZE 1024

std::string runCommand(std::string command, const char *mode)
{
    char buffer[BUFFER_SIZE];
    std::string res;
    FILE *pipe = popen((const char *)command.c_str(), mode);
    if (!pipe)
    {
        throw std::runtime_error("popen() failed");
    }
    try
    {
        while (fgets(buffer, sizeof buffer, pipe) != NULL)
        {
            res += buffer;
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
    res.pop_back();

    return res;
}

void runCommand(std::string command, const char *mode, std::vector<Process> &proc)
{
    char buffer[BUFFER_SIZE];
    FILE *pipe = popen((const char *)command.c_str(), mode);
    Time ct = Time::getCurrentTime();

    if (!pipe)
    {
        throw std::runtime_error("can't read ps command");
    }
    try
    {
        // ignore the first line
        fgets(buffer, sizeof buffer, pipe);

        std::string temp;
        while (fgets(buffer, sizeof buffer, pipe))
        {
            temp = buffer;
            temp.pop_back();
            proc.push_back({temp, ct});
        }
    }
    catch (...)
    {
        pclose(pipe);
        throw;
    }
    pclose(pipe);
}
