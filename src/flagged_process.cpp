#include "../include/flagged_process.h"

bool operator!=(const SPL::FlaggedProcess &a, const SPL::FlaggedProcess &b)
{
    return a.processName != b.processName;
}

bool operator==(const SPL::FlaggedProcess &a, const SPL::FlaggedProcess &b)
{
    return a.processName == b.processName;
}