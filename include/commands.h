#ifndef COMMANDS_H
#define COMMANDS_H

#include <string>
#include <vector>
#include "Process.h"
#include "Time.h"

std::string runCommand(std::string command, const char *mode);
void runCommand(std::string command, const char *mode, std::vector<Process> &proc);

#endif