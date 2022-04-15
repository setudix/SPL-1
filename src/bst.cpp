#include "../include/bst.h"

BST::BST()
{
    root = NULL;
}
BST::BST(MyVector<Process> &proc)
{
    BST();
    root = NULL;
    for (int i = 0; i < (int)proc.size(); i++)
        insert(proc[i]);
}
BST_Node *BST::new_node(Process &x)
{
    BST_Node *temp = new BST_Node;
    temp->data = x;
    temp->left = NULL;
    temp->right = NULL;
    temp->process_sessions.push_back(x.getActiveTime());
    return temp;
}

void BST::insert(Process &x)
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
                cur->right = new_node(x);
                return;
            }
            else
                insert(cur->right, x);
        }
        else
        {
            if (cur->left == NULL)
            {
                cur->left = new_node(x);
                return;
            }
            else
                insert(cur->left, x);
        }
    }
}

BST_Node* BST::search(std::string name)
{
    return search(root, name);
}

BST_Node* BST::search(BST_Node *cur, std::string &name)
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

void BST::printBST()
{
    printBST(root);
}

void BST::printBST(BST_Node *cur)
{
    if (cur == NULL)
        return;
    printBST(cur->left);
    cur->data.displayProcess();
    Time temp;
    for (auto time : cur->process_sessions)
    {
        temp = temp + time;
    }
    printf(" === ");
    temp.displayTime();
    puts("");

    printBST(cur->right);
}

void BST::update(BST &x)
{
    check_stopped_processes(root, x);
    add_new_nodes(x.root);
}

void BST::updateTime(BST_Node *cur, Process &x)
{   
    if (cur->data.getProcessName() == x.getProcessName())
    {
        cur->data = x;
        if (cur->stopped < (int)cur->process_sessions.size())
            cur->process_sessions[cur->stopped] = cur->data.getActiveTime();
        else 
            cur->process_sessions.push_back(cur->data.getActiveTime());

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
            updateTime(cur->right,x);
    }
    else
    {
        if (cur->left == NULL)
        {
            cur->left = new_node(x);
            return;
        }
        else
            updateTime(cur->left, x);
    }
}
void BST::add_new_nodes(BST_Node* cur)
{
    if (cur == NULL)
        return;
    
    add_new_nodes(cur->left);
    this->updateTime(this->root,cur->data);
    add_new_nodes(cur->right);

}
void BST::check_stopped_processes(BST_Node *cur, BST &x)
{
    if (cur == NULL) 
        return;
    check_stopped_processes(cur->left, x);
    if (x.search(cur->data.getProcessName()) == NULL)
        cur->stopped++;
    check_stopped_processes(cur->right, x);
}
