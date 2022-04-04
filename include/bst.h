#ifndef BST_H
#define BST_H

#include "Process.h"
#include "myvector.h"

struct BST_Node
{
    Process data;
    Time total_active_time;
    int stopped = 0;
    BST_Node *left;
    BST_Node *right;
};

class BST
{
private:
    BST_Node *root = NULL;
    BST_Node *new_node(Process &x);
    void insert(BST_Node *cur, Process &x);
    void search(BST_Node *cur, std::string &name);
    void printBST(BST_Node* cur);
    void add_new_nodes(BST_Node* cur);
    void updateTime(BST_Node* cur, Process &x);

public:
    BST();
    BST(MyVector<Process> &proc);
    void insert(Process &x);
    void search(std::string name);
    void printBST();
    void update(BST &x);
};
#endif