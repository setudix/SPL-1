#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>
#include "Process.h"
#include "Time.h"
#include "myvector.h"

namespace SPL
{
    std::string runCommand(std::string command, const char *mode);
    void runCommand(std::string command, const char *mode, std::vector<SPL::Process> &proc);
    void runCommand(std::string command, const char *mode, SPL::MyVector<SPL::Process> &proc);
}
#endif