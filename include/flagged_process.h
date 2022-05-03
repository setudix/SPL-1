#ifndef FLAGGED_PROCESS_H
#define FLAGGED_PROCESS_H

#include <string>

#include "Time.h"

namespace SPL
{
    struct FlaggedProcess
    {
        std::string processName;
        char mode;
        SPL::Time maxActiveTimeForDay;
    };
}
bool operator!=(const SPL::FlaggedProcess &a, const SPL::FlaggedProcess &b);
bool operator==(const SPL::FlaggedProcess &a, const SPL::FlaggedProcess &b);

#endif