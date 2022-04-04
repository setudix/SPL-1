#include <thread>
#include <chrono>

#include "../include/process_management.h"
#include "../include/Process.h"
#include "../include/commands.h"
#include "../include/myvector.h"
#include "../include/mysort.h"
#include "../include/bst.h"
#include "../include/Util.h"
#include "../include/Time.h"

BST* root_BST = NULL;

BST* getProcessInfoBST()
{
    MyVector<Process> *proc = new MyVector<Process>;
    runCommand(Util::getPsCommand(),"r",*proc);
    BST *temp = new BST(*proc);
    delete proc;
    return temp; 
}

void checkProcess()
{
    while (1)
    {
        if (root_BST == NULL)
        {
            root_BST = getProcessInfoBST();
            
        }
        else
        {
            BST *temp = getProcessInfoBST();
            root_BST->update(*temp);

            delete temp;
        }
        puts("--------------------------------------");
        root_BST->printBST();
        puts("**************************************");
        Time a(runCommand(Util::getCurrentTimeCommand(),"r"));
        a.displayTime();
        puts("");
        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}

void runProcessThread()
{
    std::thread p(checkProcess);
    p.join();
}