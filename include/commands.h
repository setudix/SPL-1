#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include "Process.h"
#include <vector>

std::string runCommand(std::string command, const char *mode);
void runCommand(std::string command, const char *mode, std::vector<Process> &proc);

#endif