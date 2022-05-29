#ifndef ACTIVE_TIME_H
#define ACTIVE_TIME_H

#include "Time.h"
#include "commands.h"
#include "Util.h"

#include <string>
#include <thread>
#include <fstream>

extern SPL::Time pcOnDuration; 


namespace SPL
{
    void calculatePcOnTime();
}
#endif