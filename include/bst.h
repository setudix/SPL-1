#ifndef BST_H
#define BST_H

#include <mutex>
#include <fstream>

#include "commands.h"
#include "Process.h"
#include "myvector.h"
#include "Time.h"


const std::string PROCESS_INFO_DIR = "/logs/processes/";

namespace SPL
{
    struct BST_Node
    {
        Process data;
        // SPL::Time total_active_time;
        bool active;
        int stopped = 0;
        BST_Node *left;
        BST_Node *right;
        SPL::MyVector<SPL::Time> process_sessions;
        int key_frequency[256] = {0};
    };

    class BST
    {
    private:
        BST_Node *root = NULL;
        std::mutex guard;
        BST_Node *newNode(SPL::Process &x);
        BST_Node *newNode(SPL::Process &x, bool active, int stopped, SPL::MyVector<SPL::Time> &procSessions);
        bool getStoredInfo();
        void insert(BST_Node *cur, SPL::Process &x);
        BST_Node *search(BST_Node *cur, std::string &name);
        void printBST(BST_Node *cur, int &cnt );
        void add_new_nodes(BST_Node *cur);
        void updateTime(BST_Node *cur, Process &x);
        void check_stopped_processes(BST_Node *cur, BST &x);
        void getProcessList(BST_Node *cur, SPL::MyVector<BST_Node *> &process_list);
        void insertNodesFromFile(BST_Node *cur, SPL::Process &data, bool active, int stopped, SPL::MyVector<SPL::Time> &processSessions);

    public:
        BST();
        BST(SPL::MyVector<SPL::Process> &proc);
        void insert(SPL::MyVector<SPL::Process> &proc);
        void insert(SPL::Process &x);
        BST_Node *search(std::string name);
        void printBST();
        void update(BST &x);
        SPL::MyVector<BST_Node *> *getProcessList();
        void lock();
        void unlock();
        SPL::Time getTotalActiveTime(BST_Node *cur);
        bool restorePrevSessionData();
    };
}
#endif