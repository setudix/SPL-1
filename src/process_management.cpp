#include "../include/process_management.h"
#include "../include/SafeVector.h"
#include <vector>
const std::string PROCESS_INFO_DIR = "/logs/processes/";
SPL::BST* root_BST = NULL;
void write_process_to_file(SPL::MyVector<SPL::BST_Node*> &process_list)
{
    std::fstream file;
    std::string filename = SPL::runCommand("pwd", "r") + PROCESS_INFO_DIR + SPL::runCommand(SPL::Util::getDateIn_YYYY_DD_MM(),"r") + ".dat"; 

    file.open(filename, std::ios::out);

    if (file.is_open())
    {
        std::string user;
        int pid;
        int ppid;
        std::string comm;
        int total_sessions;
        SPL::Time total_time;

        for (SPL::BST_Node *process_info_node : process_list)
        {
            user = process_info_node->data.getUser();
            pid = process_info_node->data.getPid();
            ppid = process_info_node->data.getPpid();
            comm = process_info_node->data.getProcessName();
            total_sessions = process_info_node->process_sessions.size();
            total_time.setTime(0);

            file << user << " " << pid << " " << ppid << " " << comm << " " << total_sessions << " ";

            for (SPL::Time x: process_info_node->process_sessions)
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

void write_process(SPL::BST &process_info)
{
    SPL::MyVector<SPL::BST_Node*> *process_list = process_info.getProcessList();
    write_process_to_file(*process_list);

    delete process_list;

}

SPL::BST* getProcessInfoBST()
{
    SPL::MyVector<SPL::Process> *proc = new SPL::MyVector<SPL::Process>;
    SPL::runCommand(SPL::Util::getPsCommand(),"r",*proc);
    SPL::BST *temp = new SPL::BST;

    temp->lock();
        temp->insert(*proc);
    temp->unlock();
    
    delete proc;
    return temp; 
}
namespace SPL
{
    void killProcess(SPL::BST_Node *cur)
    {
       std::string command = SPL::Util::getKillCommand();
       command += " ";
       command += std::to_string(cur->data.getPid());
       SPL::runCommand(command, "r");

    }
    void parentalControl(SPL::BST &temp_BST)
    {
        static SPL::MyVector<SPL::FlaggedProcess> listOfFlaggedProcesses;
        if ((int)listOfFlaggedProcesses.size() == 0)
        {
            static std::string flaggedProcessFileName = "flaggedProcess.txt";
            std::fstream flaggedProcessFile;
            flaggedProcessFile.open(flaggedProcessFileName, std::ios::in);

            if (!flaggedProcessFile.is_open())
                return;
            else
            {
                std::string processName;
                char mode;
                long long time;
                while (flaggedProcessFile >> processName >> mode >> time)

                    if (mode == 'd')
                    {
                        SPL::FlaggedProcess flaggedProcess;
                        flaggedProcess.processName = processName;
                        flaggedProcess.mode = mode;
                        flaggedProcess.maxActiveTimeForDay.setTime(time);
                        listOfFlaggedProcesses.push_back(flaggedProcess);
                    }
            }
            flaggedProcessFile.close();
        }
        
        for (SPL::FlaggedProcess flaggedProcess : listOfFlaggedProcesses)
        {
            root_BST->lock();
                SPL::BST_Node *prev = root_BST->search(flaggedProcess.processName);
            root_BST->unlock();

            temp_BST.lock();
                SPL::BST_Node *cur = temp_BST.search(flaggedProcess.processName);
            temp_BST.unlock();

            // current == null means that the process is not running
            if (cur == NULL)
                continue;
            else
            {
                SPL::Time tempTotalTime;
                SPL::Time *timeFromPrevSessions = new SPL::Time;
                SPL::Time *timeFromCurrentSession = new SPL::Time;

                for (int i = 0; i + 1 < (int)prev->process_sessions.size(); i++)
                    *timeFromPrevSessions = *timeFromPrevSessions + prev->process_sessions[i];

                *timeFromCurrentSession = temp_BST.getTotalActiveTime(cur);
                tempTotalTime = *timeFromPrevSessions + *timeFromCurrentSession;

                delete timeFromPrevSessions;
                delete timeFromCurrentSession;
                if (flaggedProcess.mode == 'd')
                {
                    printf("process name : %s, max time : %lld, running time: %lld\n", cur->data.getProcessName().c_str(), flaggedProcess.maxActiveTimeForDay.getTimeInSeconds(), tempTotalTime.getTimeInSeconds());
                    if (tempTotalTime > flaggedProcess.maxActiveTimeForDay)
                        killProcess(cur);
                }
            }
        }
    }

    void checkProcess()
    {
        SPL::ActiveWindow activeWindow;
        while (1)
        {
            if (root_BST == NULL)
                root_BST = getProcessInfoBST();
            else
            {
                SPL::BST *temp = getProcessInfoBST();
                root_BST->lock();
                    root_BST->update(*temp);
                root_BST->unlock();
                parentalControl(*temp);

                delete temp;
            }
            puts("--------------------------------------");
            // root_BST->printBST();
            root_BST->lock();
                // SPL::BST_Node *temp = root_BST->search(activeWindow.get_active_window_name());
                SPL::BST_Node *temp = root_BST->search("gedit");
            root_BST->unlock();
            if (temp != NULL)
            {
                // temp->data.displayProcess();
                // printf("%s\n", temp->data.getProcessName().c_str());
                // printf(" === ");
                // SPL::Time tempTime;
                // for (auto time : temp->process_sessions)
                // {
                //     time.displayTime();
                //     printf(" ");
                //     tempTime = tempTime + time;
                // }
                // puts("");
                // printf("total = ");
                // tempTime.displayTime();
                // puts("");

                temp->data.displayProcess();
                puts("");
            }
            puts("**************************************");
            SPL::Time a(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));
            a.displayTime();
            puts("");
            
            root_BST->lock();
                write_process(*root_BST);
            root_BST->unlock();

            std::this_thread::sleep_for(std::chrono::milliseconds(2000));
        }
    }
}
