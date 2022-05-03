#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H


#include <thread>
#include <chrono>
#include <fstream>
#include <atomic> 

#include "../include/Process.h"
#include "../include/commands.h"
#include "../include/myvector.h"
#include "../include/mysort.h"
#include "../include/bst.h"
#include "../include/Util.h"
#include "../include/Time.h"
#include "../include/active_window.h"
#include "../include/flagged_process.h"

extern SPL::BST* root_BST;

namespace SPL
{
    void checkProcess();
}
#endif
