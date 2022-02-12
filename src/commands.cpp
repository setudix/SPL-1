#include <cstdio>
#include <iostream>
#include <stdexcept>
#include <sys/stat.h>
#include <string>
#include "../include/commands.h"
#include "../include/mystring.h"

#define BUFFER_SIZE 128
#define STR_SIZE 1024

std::string runCommand(const char *command, const char *mode)
{
    char buffer[BUFFER_SIZE];
    std::string res;
    FILE *pipe = popen(command, mode);
    if (!pipe)
        throw std::runtime_error("popen() failed");
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
