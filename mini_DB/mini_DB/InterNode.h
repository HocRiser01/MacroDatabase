#pragma once
#include"Structure.h"
#include"Node.h"
#define M 2
class Inter_Node : public Node
{
public:
    Inter_Node();
    virtual ~Inter_Node();
    bool Insert(structure value, Node* pNode);
    bool Delete(structure value);
    structure Split(Inter_Node* pNode, structure key);
    bool Merge(Inter_Node* pNode);
    bool Slib(Inter_Node* pNode);
    Node* Child[M * 2 + 1];
};
