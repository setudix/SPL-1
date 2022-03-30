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

int main()
{
    std::string uptime = runCommand(Util::getUptimeCommand(), "r");
    std::string current_time = runCommand(Util::getCurrentTimeCommand(), "r");

    // printf("uptime\n");
    // printf("from system command : %s\n, my parsed output : %s\n",uptime.c_str(),)
    // // Time t1(uptime);
    // Time t2(current_time);

    // t1.displayTime();
    // t2.displayTime();

    // Time t3 = t1 + t2;
    // t3.displayTime();
    // t3 = t1 - t2;
    // t3.displayTime();

    // runThreads();

    // std::vector<Process> proc;
    // runCommand(Util::getPsCommand(), "r", proc);

    // MyVector<Process> proc_test;
    // runCommand(Util::getPsCommand(), "r", proc_test);

    // Process::sortProcess(proc);
    // puts("-----------------");
    // Time ct = runCommand(Util::getCurrentTimeCommand(), "r");
    int cnt = 0;
    // for (auto x : proc)
    // {
    //     printf("%d. ", ++cnt);
    //     x.displayProcess();
    //     Time t = x.getRunningFor(current_time);
    //     printf(" running for ");
    //     t.displayTime();
    //     puts("");
    // }

    // std::vector<Process> unique_proc;
    // unique_proc = getUniqueProcessForUser(proc, runCommand("whoami", "r"));
    // Process::sortProcessByActiveTime(unique_proc);
    // cnt = 0;
    // // for (auto x : unique_proc)
    // {
    //     printf("%d. ", ++cnt);
    //     x.displayProcessWithActiveTime();
    //     puts("");
    // }

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



    //// CUSTOM VECTOR TEST /////

    MyVector<int> temp;
    for (int i=0;i<10;i++){
        temp.push_back(rand());
    }

    for (int x : temp)
        printf("%d ", x % 100);

    puts("");

    std::sort(temp.begin(),temp.end());
    for (int x : temp)
        printf("%d ", x % 100);

    puts("");


    return 0;
}
