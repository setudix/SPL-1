#include <thread>
#include <chrono>
#include <fstream>

#include "../include/process_management.h"
#include "../include/Process.h"
#include "../include/commands.h"
#include "../include/myvector.h"
#include "../include/mysort.h"
#include "../include/bst.h"
#include "../include/Util.h"
#include "../include/Time.h"

const std::string PROCESS_INFO_DIR = "/logs/processes/";
BST* root_BST = NULL;

void write_process_to_file(MyVector<BST_Node*> &process_list)
{
    std::fstream file;
    std::string filename = runCommand("pwd", "r") + PROCESS_INFO_DIR + runCommand(Util::getDateIn_YYYY_DD_MM(),"r") + ".dat"; 

    file.open(filename, std::ios::out);

    if (file.is_open())
    {
        std::string user;
        int pid;
        int ppid;
        std::string comm;
        int total_sessions;
        Time total_time;

        for (BST_Node *process_info_node : process_list)
        {
            user = process_info_node->data.getUser();
            pid = process_info_node->data.getPid();
            ppid = process_info_node->data.getPpid();
            comm = process_info_node->data.getProcessName();
            total_sessions = process_info_node->process_sessions.size();
            total_time.setTime(0);

            file << user << " " << pid << " " << ppid << " " << comm << " " << total_sessions << " ";

            for (Time x: process_info_node->process_sessions)
            {
                file << x.getTimeInSeconds() << " ";
                total_time = total_time + x;
            }

            file << total_time.getTimeInSeconds() << "\n";
        }
        file.close();

    }
    else 
        printf("can't open file for writing processes\n");
}

void write_process(BST &process_info)
{
    MyVector<BST_Node*> *process_list = process_info.getProcessList();
    write_process_to_file(*process_list);

    delete process_list;

}

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
        // puts("--------------------------------------");
        // // root_BST->printBST();
        // BST_Node* temp = root_BST->search("gedit");
        // if (temp != NULL)
        // {
        //     // temp->data.displayProcess();
        //     printf(" === ");
        //     Time tempTime;
        //     for (auto time : temp->process_sessions)
        //     {
        //         time.displayTime();
        //         printf(" ");
        //         tempTime = tempTime + time;
        //     }
        //     puts("");
        //     printf("total = ");
        //     tempTime.displayTime();
        //     puts("");
            
        // }
        // puts("**************************************");
        // Time a(runCommand(Util::getCurrentTimeCommand(),"r"));
        // a.displayTime();
        // puts("");
        write_process(*root_BST);

        std::this_thread::sleep_for(std::chrono::milliseconds(5000));
    }
}
