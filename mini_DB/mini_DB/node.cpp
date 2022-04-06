#include<iostream>
#include"Node.h"
#include"InterNode.h"
using namespace std;

Node::Node()
{
    isLeaf = true;
    count = 0;
    Parent = nullptr;
}

Node::~Node(){}

Node* Node::GetBrother(int& flag)
{
    if (Parent == nullptr)
        return nullptr;

    Node* p = nullptr;
    for (int i = 0; i <= Parent->count; i++)
    {
        if (Parent->Child[i] == this)
        {
            if (i == Parent->count)
            {
                p = Parent->Child[i - 1];
                flag = 1;
            }
            else
            {
                p = Parent->Child[i + 1];
                flag = 2;
            }
        }
    }
    return p;
}

void Node::Print()
{
    for (int i = 0; i < count; i++)
    {
        cout << "(" << key[i].line1 <<  ")  ";
        if (i >= count - 1)
            cout << " | ";
    }
}
