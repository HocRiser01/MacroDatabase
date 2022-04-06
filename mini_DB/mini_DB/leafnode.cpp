#include"LeafNode.h"

Leaf_Node::Leaf_Node()
{
    isLeaf = true;
    Pre_Node = nullptr;
    Next_Node = nullptr;
}

Leaf_Node::~Leaf_Node(){
}

bool Leaf_Node::Insert(structure value)
{
    int i = 0;
    for (; (value.larger_than_second(key[i],type_of_key)) && (i < count); i++)
    {
    }
    for (int j = count; j > i; j--)
        key[j] = key[j - 1];
    key[i] = value;
    count++;
    return true;
}

bool Leaf_Node::Delete(structure value)
{
    bool found = false;
    int i = 0;
    for (; i < count; i++)
    {
        if (value.same_to_second(key[i], type_of_key))
        {
            found = true;
            break;
        }
    }
    if (false == found)
        return false;
    int j = i;
    for (; j < count - 1; j++)
        key[j] = key[j + 1];
    key[j].clear();
    count--;
    return true;
}

structure Leaf_Node::Split(Leaf_Node* p)
{
    int j = 0;
    for (int i = M; i < M * 2; i++, j++)
        p->key[j] = this->key[i];
    this->count = this->count - j;
    p->count = j;
    return p->key[0];
}

bool Leaf_Node::Merge(Leaf_Node* p)
{
    if (this->count + p->count > M * 2)
        return false;
    for (int i = 0; i < p->count; i++)
        this->Insert(p->key[i]);
    return true;
}
