#pragma once
#include"Structure.h"
#include"Node.h"
#include"InterNode.h"
class Leaf_Node : public Node
{
public:
    Leaf_Node();
    virtual ~Leaf_Node();
    bool Insert(structure value);
    bool Delete(structure value);
    structure Split(Leaf_Node* pNode);
    bool Merge(Leaf_Node* pNode);
    Leaf_Node* Pre_Node;
    Leaf_Node* Next_Node;
};