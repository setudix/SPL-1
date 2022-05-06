#include "../include/bst.h"

SPL::BST::BST()
{
    root = NULL;
}
SPL::BST::BST(SPL::MyVector<SPL::Process> &proc)
{
    SPL::BST();
    root = NULL;
    insert(proc);
}
void SPL::BST::insert(SPL::MyVector<SPL::Process> &proc)
{
    for (int i = 1; i < (int)proc.size(); i++)
        insert(proc[i]);
}
SPL::BST_Node *SPL::BST::newNode(SPL::Process &x)
{
    SPL::BST_Node *temp = new SPL::BST_Node;
    temp->data = x;
    temp->active = true;
    temp->left = NULL;
    temp->right = NULL;
    temp->process_sessions.push_back(x.getActiveTime());
    return temp;
}
SPL::BST_Node* SPL::BST::newNode(SPL::Process &x, bool active, int stopped,SPL::MyVector<SPL::Time> &procSessions)
{
    SPL::BST_Node *temp = new SPL::BST_Node;
    temp->data = x;
    temp->active = active;
    temp->stopped = stopped;
    temp->left = NULL;
    temp->right = NULL;
    
    for (SPL::Time t : procSessions)
        temp->process_sessions.push_back(t);

    return temp;
}
void SPL::BST::insert(SPL::Process &x)
{
    insert(root, x);
}
void SPL::BST::insert(SPL::BST_Node *cur, SPL::Process &x)
{
    if (root == NULL)
    {
        root = new SPL::BST_Node;
        root->data = x;
        root->active = true;
        root->left = NULL;
        root->right = NULL;
        root->process_sessions.push_back(x.getActiveTime());
        return;
    }

    else
    {
        if (cur->data.getProcessName() == x.getProcessName())
        {
            // not yet entirely sure how this should work.
            // for now it should just update if we find a process which
            // was started before the one that is in the bst.
            if (cur->data.getTime() > x.getTime())
                cur->data = x;
            return;
        }
        if (cur->data < x)
        {
            if (cur->right == NULL)
            {
                cur->right = newNode(x);
                return;
            }
            else
                insert(cur->right, x);
        }
        else
        {
            if (cur->left == NULL)
            {
                cur->left = newNode(x);
                return;
            }
            else
                insert(cur->left, x);
        }
    }
}

SPL::BST_Node* SPL::BST::search(std::string name)
{
    return search(root, name);
}

SPL::BST_Node* SPL::BST::search(SPL::BST_Node *cur, std::string &name)
{
    if (cur == NULL)
        return NULL;
    if (cur->data.getProcessName() == name)
        return cur;
    if (cur->data.getProcessName() < name)
        return search(cur->right, name);
    else
        return search(cur->left, name);
}

void SPL::BST::printBST()
{
    int cnt = 0;
    printBST(root,cnt);
}

void SPL::BST::printBST(SPL::BST_Node *cur, int &cnt)
{
    if (cur == NULL)
        return;
    printBST(cur->left,cnt);
    printf("%d.  ",++cnt);
    cur->data.displayProcess();
    SPL::Time temp;
    for (auto time : cur->process_sessions)
    {
        temp = temp + time;
    }
    printf(" === ");
    temp.displayTime();
    puts("");

    printBST(cur->right,cnt);
}

void SPL::BST::update(SPL::BST &x)
{
    check_stopped_processes(root, x);
    puts("CHECK DONE: STOPPED PROCESS");
    add_new_nodes(x.root);
    puts("CHECK DONE: TIME UPDATE");
}

void SPL::BST::updateTime(SPL::BST_Node *cur, SPL::Process &x)
{   
    if (cur->data.getProcessName() == x.getProcessName())
    {
        cur->data = x;
        if (cur->active)
            cur->process_sessions[cur->stopped] = cur->data.getActiveTime();
        else 
        {
            printf("Process new session: %s\n", cur->data.getProcessName().c_str());
            cur->process_sessions.push_back(cur->data.getActiveTime());
            cur->active = true;
        }
        return;
    }
    if (cur->data < x)
    {
        if (cur->right == NULL)
        {
            cur->right = newNode(x);
            return;
        }
        else
            updateTime(cur->right,x);
    }
    else
    {
        if (cur->left == NULL)
        {
            cur->left = newNode(x);
            return;
        }
        else
            updateTime(cur->left, x);
    }
}
void SPL::BST::add_new_nodes(SPL::BST_Node* cur)
{
    if (cur == NULL)
        return;
    
    add_new_nodes(cur->left);
    this->updateTime(this->root,cur->data);
    add_new_nodes(cur->right);

}
void SPL::BST::check_stopped_processes(SPL::BST_Node *cur, SPL::BST &x)
{
    puts("-----IN: CHECK_STOPPED_PROCESS----");
    if (cur == NULL) 
        return;
    check_stopped_processes(cur->left, x);
    if (x.search(cur->data.getProcessName()) == NULL)
        {
            if (cur->active)
            {
                cur->stopped++;
                cur->active = false;
                printf("process : %s is stopped\n" , cur->data.getProcessName().c_str());
            }

                
        }
    check_stopped_processes(cur->right, x);
}

SPL::MyVector<SPL::BST_Node*>* SPL::BST::getProcessList()
{
    SPL::MyVector<SPL::BST_Node*> *process_list = new SPL::MyVector<SPL::BST_Node*>;
    getProcessList(root, *process_list);
    return process_list;
}

void SPL::BST::getProcessList(SPL::BST_Node* cur, SPL::MyVector<SPL::BST_Node*> &process_list)
{
    if (cur == NULL)
        return;
    getProcessList(cur->left, process_list);
    process_list.push_back(cur);
    getProcessList(cur->right, process_list);
}

void SPL::BST::lock()
{
    guard.lock();
}

void SPL::BST::unlock()
{
    guard.unlock();
}

SPL::Time SPL::BST::getTotalActiveTime(SPL::BST_Node* cur) 
{
    SPL::Time totalTime;

    for (SPL::Time t : cur->process_sessions)
        totalTime = totalTime + t;

    return totalTime;
}
bool SPL::BST::getStoredInfo()
{
    std::fstream file;
    std::string filename = SPL::runCommand("pwd", "r") + PROCESS_INFO_DIR + SPL::runCommand(SPL::Util::getDateIn_YYYY_DD_MM(),"r") + ".dat";
    
    file.open(filename, std::ios::in);
    if (!file.is_open())
    {
        printf("First session of this day.\n");
        return 0;
    }
    else
    {
        puts("PROCESS FETCHED FROM FILE");
        std::string user;
        int pid;
        int ppid;
        std::string comm;
        long long startTime;
        long long activeTime;
        long long lastActive;

        bool active;
        int stopped;
        int cnt = 0;
        while (file >> user >> pid >> ppid >> comm >> startTime >> activeTime >> lastActive >> active >> stopped)
        {
            cnt++;
            SPL::MyVector<SPL::Time> *processSessions = new SPL::MyVector<SPL::Time>;
            for (int i=0;i<stopped;i++)
            {
                long long sessionTime;
                file >> sessionTime;

                SPL::Time *tempSessionTime = new SPL::Time;
                tempSessionTime->setTime(sessionTime);

                processSessions->push_back(*tempSessionTime);

                delete tempSessionTime;
            }
            // printf("%d. name = %s, process sessions : %d\n",cnt, comm.c_str(), stopped); 
            SPL::Process *tempProcess = new SPL::Process(user,pid,ppid,comm,startTime,activeTime,lastActive);
            insertNodesFromFile(root, *tempProcess, active, stopped, *processSessions);
            delete processSessions;
            delete tempProcess;
        }
        file.close();
        puts("FETCH DONE");
        return 1;
    }    
}

void SPL::BST::insertNodesFromFile(BST_Node *cur, SPL::Process &data, bool active, int stopped, SPL::MyVector<SPL::Time> &processSessions)
{
    if (root == NULL)
    {
        root = new SPL::BST_Node;
        root->data = data;
        root->active = active;
        root->stopped = stopped;
        root->left = NULL;
        root->right = NULL;
        for (SPL::Time x : processSessions)
            root->process_sessions.push_back(x);

        return;
    }
    else
    {
        if (cur->data < data)
        {
            if (cur->right == NULL)
            {
                cur->right = newNode(data, active, stopped, processSessions);
                return;
            }
            else 
                insertNodesFromFile(cur->right, data, active, stopped, processSessions);
        }
        else if (cur->data > data) 
        {
            if (cur->left == NULL)
            {
                cur->left = newNode(data, active, stopped, processSessions);
                return;
            }
            else 
                insertNodesFromFile(cur->left, data, active, stopped, processSessions);
        }

    }
}
bool SPL::BST::restorePrevSessionData()
{
    return getStoredInfo();
}