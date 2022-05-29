#include "../include/process_management.h"
#include "../include/SafeVector.h"
#include <vector>
SPL::BST* root_BST = NULL;
bool isDataRestored = false;

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
        long long  startTime; 
        long long activeTime;
        long long lastActive;

        bool active;
        bool user_opened;
        int stopped;
        
        for (SPL::BST_Node *process_info_node : process_list)
        {
            user = process_info_node->data.getUser();
            pid = process_info_node->data.getPid();
            ppid = process_info_node->data.getPpid();
            comm = process_info_node->data.getProcessName();
            startTime = process_info_node->data.getTime().getTimeInSeconds();
            activeTime = process_info_node->data.getActiveTime().getTimeInSeconds();
            lastActive = process_info_node->data.getLastActiveTime().getTimeInSeconds();

            // it will remain false as the data will be fetched when the system restarts
            active = false;
            user_opened = process_info_node->user_opened;
            stopped = (int)process_info_node->process_sessions.size();

            file << user << " ";
            file << pid << " ";
            file << ppid << " ";
            file << comm << " ";
            file << startTime << " ";
            file << activeTime << " ";
            file << lastActive << " ";

            file << active << " ";
            file << user_opened << " ";
            file << stopped << " ";
            if (stopped != 1)
                for (SPL::Time x: process_info_node->process_sessions)
                    file << ((x.getTimeInSeconds() == 0)? 0 : x.getTimeInSeconds()) << " ";

            else 
            {
                if (activeTime == 0)
                    file << 0 << " ";
                else 
                    for (SPL::Time x: process_info_node->process_sessions)
                        file << x.getTimeInSeconds() << " ";
            }

            for (int keyFreq : process_info_node->key_frequency)
                file << keyFreq << " ";
                
            file << "\n";
        }
        file.close();

    }
    else 
        printf("can't open file for writing processes\n");
}

void write_process(SPL::BST &process_info)
{
    SPL::MyVector<SPL::BST_Node*> *process_list = process_info.getProcessList();
    //sorting the process aquired from bst by their process pid 
    SPL::quicksort<SPL::BST_Node*>(*process_list, [](SPL::BST_Node* &a, SPL::BST_Node* &b)
    {
        return a->data.getPid() < b->data.getPid();
    }); 
    write_process_to_file(*process_list);

    delete process_list;

}

SPL::BST* getProcessInfoBST()
{
    SPL::MyVector<SPL::Process> *proc = new SPL::MyVector<SPL::Process>;
    SPL::BST *temp = new SPL::BST;

    auto getProcInfo = [&](){
        temp->lock();
            SPL::runCommand(SPL::Util::getPsCommand(),"r",*proc);
            temp->insert(*proc);
        temp->unlock();
    };

    if (isDataRestored)
    {
        // puts("-----RUNNING PS COMMAND----");
        getProcInfo();
        // puts("-----DONE RUNNING PS COMMAND");
    }
    else 
    {
        bool check;
        temp->lock();
            check = temp->restorePrevSessionData();
        temp->unlock();
        if (!check)
            getProcInfo();
        isDataRestored = true;
    }
    
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
                    if (tempTotalTime > flaggedProcess.maxActiveTimeForDay)
                        killProcess(cur);
                }
            }
        }
    }

    void checkProcess()
    {
        SPL::ActiveWindow activeWindow;
        auto f = [](int sig){
            write_process(*root_BST);
            delete root_BST;
            exit(0);
            };
        while (1)
        {
            if (root_BST == NULL)
            {   
                root_BST = getProcessInfoBST();
                continue;
            }
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
            root_BST->lock();
                SPL::BST_Node *temp = root_BST->search(activeWindow.get_active_window_name());
                if (temp != NULL)
                {
                    temp->user_opened = true;
                    printf("%s\n", temp->data.getProcessName().c_str());
                    printf(" === ");
                    SPL::Time tempTime;
                    for (auto time : temp->process_sessions)
                    {
                        time.displayTime();
                        printf(" ");
                        tempTime = tempTime + time;
                    }
                    puts("");
                    printf("total = ");
                    tempTime.displayTime();
                    puts("");

                    puts("");
                }
            root_BST->unlock();
            puts("**************************************");
            // SPL::Time a(SPL::runCommand(SPL::Util::getCurrentTimeCommand(), "r"));
            // a.displayTime();
            // puts("");

            
            
            root_BST->lock();
                write_process(*root_BST);
            root_BST->unlock();

            signal(SIGINT,f);
            std::this_thread::sleep_for(std::chrono::milliseconds(3000));
        }
    }
}
