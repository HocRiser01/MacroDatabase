#pragma once
#include"Structure.h"
#include"Node.h"
#include"InterNode.h"
#include"LeafNode.h"
class Bplus
{
public:
    Bplus();
    virtual ~Bplus();
    datachunk_manager* Search(structure data);
    bool Insert(structure data, datachunk* data_point);
    bool Delete(structure data);
    void Print();
    int type_of_key;
protected:
    Leaf_Node* Find(structure data);
    bool Add_Node(Inter_Node* pNode, structure key, Node* New_Node);
    bool Remove_Node(Inter_Node* pNode, structure key);
    Node* Root;
};