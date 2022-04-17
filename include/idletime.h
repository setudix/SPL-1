#ifndef IDLETIME_H
#define IDLETIME_H

#include "Time.h"

extern bool is_idle;
extern SPL::Time InactivityStart;
namespace SPL
{
    void elapsedTime();
}
#endif