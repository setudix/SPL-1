#include "../include/bst.h"

BST::BST()
{
    root = NULL;
}
BST::BST(std::vector<Process> &proc)
{
    BST();
    for (int i = 0; i < (int)proc.size(); i++)
    {
        insert(proc[i]);
    }
}
BST_Node *BST::new_node(Process &x)
{
    BST_Node *temp = new BST_Node;
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;

    return temp;
}

void BST::insert(Process x)
{
    insert(root, x);
}
void BST::insert(BST_Node *cur, Process &x)
{
    if (root == NULL)
    {
        root = new BST_Node;
        root->data = x;
        root->left = NULL;
        root->right = NULL;
        return;
    }

    else
    {
        if (cur->data.getProcessName() == x.getProcessName())
        { // **not final ** need to work on it later.
            cur->data = x;
            return;
        }
        if (cur->data < x)
        {
            if (cur->right == NULL)
            {
                cur->right = new_node(x);
                return;
            }
            else
            {
                insert(cur->right, x);
            }
        }
        else
        {
            if (cur->left == NULL)
            {
                cur->left = new_node(x);
                return;
            }
            else
            {
                insert(cur->left, x);
            }
        }
    }
}

void BST::search(std::string name)
{
    search(root, name);
}

void BST::search(BST_Node *cur, std::string &name)
{
    if (cur == NULL)
    {
        printf("Process not found!\n");
        return;
    }
    if (cur->data.getProcessName() == name)
    {
        cur->data.displayProcessWithActiveTime();
        puts("");
        return;
    }
    if (cur->data.getProcessName() < name)
    {
        search(cur->right, name);
    }
    else
    {
        search(cur->left, name);
    }
}