#ifndef BST_H
#define BST_H

#include "Process.h"
#include "myvector.h"
#include "Time.h"

namespace SPL
{
    struct BST_Node
    {
        Process data;
        SPL::Time total_active_time;
        int stopped = 0;
        BST_Node *left;
        BST_Node *right;
        SPL::MyVector<SPL::Time> process_sessions;
    };

    class BST
    {
    private:
        BST_Node *root = NULL;
        BST_Node *new_node(Process &x);
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
        void insert(SPL::Process &x);
        BST_Node *search(std::string name);
        void printBST();
        void update(BST &x);
        SPL::MyVector<BST_Node *> *getProcessList();
    };
}
#endif