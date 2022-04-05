#pragma once
#include"Structure.h"
#define M 2
class Inter_Node;
class Node
{
public:
    Node();
    virtual ~Node();
    Node* GetBrother(int& flag);
    void Print();
    Inter_Node* Parent;
    structure key[M * 2];//4
    int type_of_key;
    int count;
    int isLeaf;
};