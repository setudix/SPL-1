#ifndef BST_H
#define BST_H

#include "Process.h"

struct BST_Node
{
    Process data;
    BST_Node *left;
    BST_Node *right;
};

class BST
{
private:
    BST_Node *root;
    BST_Node *new_node(Process &x);
    void insert(BST_Node *cur, Process &x);
    void search(BST_Node *cur, std::string &name);
public:
    BST();
    BST(std::vector<Process> &proc);
    void insert(Process x);
    void search(std::string name);
};
#endif