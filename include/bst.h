#ifndef BST_H
#define BST_H

#include <mutex>

#include "Process.h"
#include "myvector.h"
#include "Time.h"

namespace SPL
{
    struct BST_Node
    {
        Process data;
        // SPL::Time total_active_time;
        int stopped = 0;
        bool active;
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
        BST_Node *newNode(Process &x);
        void insert(BST_Node *cur, Process &x);
        BST_Node *search(BST_Node *cur, std::string &name);
        void printBST(BST_Node *cur);
        void add_new_nodes(BST_Node *cur);
        void updateTime(BST_Node *cur, Process &x);
        void check_stopped_processes(BST_Node *cur, BST &x);
        void getProcessList(BST_Node *cur, MyVector<BST_Node *> &process_list);

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
    };
}
#endif