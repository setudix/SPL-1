#ifndef __linux__
#error
#endif
#include <iostream>
#include <string>
#include <thread>
#include <algorithm>

#include "../include/mystring.h"
#include "../include/Time.h"
#include "../include/commands.h"
#include "../include/idletime.h"
#include "../include/InputDevice.h"
#include "../include/Util.h"
#include "../include/Process.h"
#include "../include/bst.h"
#include "../include/myvector.h"
#include "../include/mysort.h"

int main()
{
    std::string uptime = runCommand(Util::getUptimeCommand(), "r");
    std::string current_time = runCommand(Util::getCurrentTimeCommand(), "r");


    // runThreads();

    // std::vector<Process> proc;
    // runCommand(Util::getPsCommand(), "r", proc);

    MyVector<Process> proc_test;
    runCommand(Util::getPsCommand(), "r", proc_test);
    // quicksort<Process>(proc_test);
    // for (int i=0;i<(int)proc_test.size();i++)
    // {
    //     proc_test[i].displayProcessWithActiveTime();
    //     puts("");
    // }

    for (auto x : proc_test)
    {
        x.displayProcessWithActiveTime();
        puts("");
    }
    
    puts("---------------------------------------");
    Process::sortProcessByActiveTime(proc_test);

    for (auto x : proc_test)
    {
        x.displayProcessWithActiveTime();
        puts("");
    }
    

    // BST bst_test(unique_proc);
    // while (1)
    // {
    //     std::string x;
    //     std::cin >> x;

    //     bst_test.search(x);
    // }
    // std::pair<std::string, long long int> shouldKill({"firefox", 5});

    // while (1)
    // {

    //     std::vector<Process> test;
    //     runCommand(Util::getPsCommand(), "r", test);
    //     Process::sortProcess(test);
    //     std::vector<Process> test2;
    //     test2 = getUniqueProcessForUser(test, runCommand("whoami", "r"));
    //     bool killed = 0;
    //     for (auto x : test2)
    //     {
    //         if (x.getProcessName() == shouldKill.first)
    //         {
    //             if (x.getActiveTime().getTimeInSeconds() > shouldKill.second)
    //             {
    //                 x.killProcess();
    //                 killed = 1;
    //             }
    //         }
    //         if (killed)
    //             break;
    //     }

    //     if (killed)
    //     {
    //         printf("process %s has been killed\n", shouldKill.first.c_str());
    //         break;
    //     }
    // }

    // BST main_proc_bst(proc);
    // main_proc_bst.printBST();





    return 0;
}
