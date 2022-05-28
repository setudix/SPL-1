#ifndef PROCESS_MANAGEMENT_H
#define PROCESS_MANAGEMENT_H


#include <thread>
#include <chrono>
#include <fstream>
#include <atomic> 
#include <csignal>

#include "Process.h"
#include "commands.h"
#include "myvector.h"
#include "mysort.h"
#include "bst.h"
#include "Util.h"
#include "Time.h"
#include "active_window.h"
#include "flagged_process.h"
#include "keycodes.h"

extern SPL::BST* root_BST;

namespace SPL
{
    void checkProcess();
}
#endif
