#include<iostream>
#include<queue>
#include<vector>
#include "B_plus.h"
using namespace std;

Bplus::Bplus()
{
    Root = nullptr;
}

Bplus::~Bplus() {}

datachunk_manager* Bplus::Search(structure data)
{
    int i = 0;
    Node* p = Root;
    if (p == nullptr)
        return nullptr;
    Inter_Node* q;
    while (p != nullptr)
    {
        if (p->isLeaf)
            break;
        for (i = 0; (i < p->count) && (p->key[i].smaller_than_second(data,type_of_key) || p->key[i].same_to_second(data, type_of_key)); i++)
        {
        }
//        int k = i > 0 ? i - 1 : i;
        q = (Inter_Node*)p;
        p = q->Child[i];
    }
    if (p == nullptr)
        return nullptr;
    int found = -1;
    for (i = 0; i < p->count; i++)
    {
        if (data.same_to_second(p->key[i],type_of_key))
            found = i;
    }
    if (found >= 0)
    {
        //cout << data.line1 << " " << p->key[found].position << " " << p->key[found].line1 << endl;
        return p->key[found].pposition;
    }
    else
    {
        return nullptr;
    }
}

bool Bplus::Insert(structure data,datachunk* data_point)
{
    if (nullptr != Search(data)) {
        //cout << "Already have one!" << endl;
        datachunk_manager* mid_list = Search(data);
        mid_list = datachunk_insert(mid_list, data_point);
        return true;
    }
    data.pposition = new datachunk_manager;
    data.pposition->position = data_point;
    data.pposition->next = nullptr;
    Leaf_Node* Old_Node = Find(data);

    if (Old_Node == nullptr)
    {
        Old_Node = new Leaf_Node;
        Old_Node->type_of_key = type_of_key;
        Root = Old_Node;
    }

    if (Old_Node->count < M * 2) {
        return Old_Node->Insert(data);

    }

    Leaf_Node* New_Node = new Leaf_Node;
    New_Node->type_of_key = type_of_key;

    structure k = Old_Node->Split(New_Node);

    Leaf_Node* OldNext = Old_Node->Next_Node;
    Old_Node->Next_Node = New_Node;
    New_Node->Next_Node = OldNext;
    New_Node->Pre_Node = Old_Node;

    if (OldNext != nullptr)
        OldNext->Pre_Node = New_Node;

    if (data.smaller_than_second(k,type_of_key))
    {
        Old_Node->Insert(data);
    }
    else
    {
        New_Node->Insert(data);
    }
    Inter_Node* parent = (Inter_Node*)(Old_Node->Parent);

    if (parent == nullptr)
    {
        Inter_Node* New_Root = new Inter_Node;
        New_Root->type_of_key = type_of_key;
        New_Root->Child[0] = Old_Node;
        New_Root->key[0] = k;
        New_Root->Child[1] = New_Node;
        Old_Node->Parent = New_Root;
        New_Node->Parent = New_Root;
        New_Root->count = 1;
        Root = New_Root;
        return true;
    }

    return Add_Node(parent, k, New_Node);
}

bool Bplus::Delete(structure data)
{
    if (Search(data) == nullptr) {
        return false;
    }
    Leaf_Node* Old_Node = Find(data);
    if (Old_Node == nullptr)
        return false;
    if (false == Old_Node->Delete(data))
        return false;
    Inter_Node* parent = (Inter_Node*)(Old_Node->Parent);
    if (parent == nullptr)
    {
        if (0 == Old_Node->count)
        {
            delete Old_Node;
            Root = nullptr;
        }
        return true;
    }
    if (Old_Node->count >= M)
    {
        for (int i = 0; (i < parent->count) && (parent->key[i].smaller_than_second(data, type_of_key) || parent->key[i].same_to_second(data, type_of_key)); i++)
        {
            if (parent->key[i].same_to_second(data,type_of_key))
                parent->key[i] = Old_Node->key[0];
        }
        return true;
    }
    int flag = 1;
    Leaf_Node* Brother = (Leaf_Node*)(Old_Node->GetBrother(flag));
    structure NewData;
    NewData.clear();
    if (Brother->count > M)
    {
        if (1 == flag)
        {
            NewData = Brother->key[Brother->count - 1];
        }
        else
        {
            NewData = Brother->key[0];
        }
        Old_Node->Insert(NewData);
        Brother->Delete(NewData);
        if (1 == flag)
        {
            for (int i = 0; i <= parent->count; i++)
            {
                if (parent->Child[i] == Old_Node && i > 0)
                    parent->key[i - 1] = Old_Node->key[0];
            }
        }
        else
        {
            for (int i = 0; i <= parent->count; i++)
            {
                if (parent->Child[i] == Old_Node && i > 0)
                    parent->key[i - 1] = Old_Node->key[0];
                if (parent->Child[i] == Brother && i > 1)
                    parent->key[i - 1] = Brother->key[0];
            }
        }
        return true;
    }
    structure NewKey;
    NewKey.clear();
    if (1 == flag)
    {
        Brother->Merge(Old_Node);
        NewKey = Old_Node->key[0];
        Leaf_Node* OldNext = Old_Node->Next_Node;
        Brother->Next_Node = OldNext;
        if (OldNext != nullptr)
            OldNext->Pre_Node = Brother;
        delete Old_Node;
    }
    else
    {
        Old_Node->Merge(Brother);
        NewKey = Brother->key[0];
        Leaf_Node* OldNext = Brother->Next_Node;
        Old_Node->Next_Node = OldNext;
        if (OldNext != nullptr)
            OldNext->Pre_Node = Old_Node;
        delete Brother;
    }
    return Remove_Node(parent, NewKey);
}

Leaf_Node* Bplus::Find(structure data)
{
    int i = 0;
    Node* p = Root;
    Inter_Node* q;
    while (p != nullptr)
    {
        if (p->isLeaf)
            break;
        for (i = 0; i < p->count; i++)
        {
            if (data.smaller_than_second(p->key[i],type_of_key))
                break;
        }
        q = (Inter_Node*)p;
        p = q->Child[i];
    }

    return (Leaf_Node*)p;
}

bool Bplus::Add_Node(Inter_Node* p, structure k, Node* New_Node)
{
    if (p == nullptr || p->isLeaf)
        return false;
    if (p->count < M * 2)
        return p->Insert(k, New_Node);
    Inter_Node* Brother = new Inter_Node;
    Brother->type_of_key = type_of_key;
    structure NewKey = p->Split(Brother, k);

    if (p->count < Brother->count)
    {
        p->Insert(k, New_Node);
    }
    else if (p->count > Brother->count)
    {
        Brother->Insert(k, New_Node);
    }
    else
    {
        Brother->Child[0] = New_Node;
        New_Node->Parent = Brother;
    }
    Inter_Node* parent = (Inter_Node*)(p->Parent);
    if (parent == nullptr)
    {
        parent = new Inter_Node();
        parent->Child[0] = p;
        parent->key[0] = NewKey;
        parent->Child[1] = Brother;
        p->Parent = parent;
        Brother->Parent = parent;
        parent->count = 1;
        Root = parent;
        return true;
    }
    return Add_Node(parent, NewKey, Brother);
}

bool Bplus::Remove_Node(Inter_Node* p, structure k)
{
    if (false == p->Delete(k))
    {
        return false;
    }
    Inter_Node* parent = (Inter_Node*)(p->Parent);
    if (parent == nullptr)
    {
        if (0 == p->count)
        {
            Root = p->Child[0];
            delete p;
        }
        return true;
    }
    if (p->count >= M)
    {
        for (int i = 0; (i < parent->count) && (parent->key[i].smaller_than_second(k, type_of_key) || parent->key[i].same_to_second(k, type_of_key)); i++)
        {
            if (parent->key[i].same_to_second(k,type_of_key))
                parent->key[i] = p->key[0];
        }
        return true;
    }
    int flag = 1;
    Inter_Node* Brother = (Inter_Node*)(p->GetBrother(flag));
    if (Brother->count > M)
    {
        p->Slib(Brother);
        if (1 == flag)
        {
            for (int i = 0; i <= parent->count; i++)
            {
                if (parent->Child[i] == p && i > 0)
                    parent->key[i - 1] = p->key[0];
            }
        }
        else
        {
            for (int i = 0; i <= parent->count; i++)
            {
                if (parent->Child[i] == p && i > 0)
                    parent->key[i - 1] = p->key[0];
                if (parent->Child[i] == Brother && i > 0)
                    parent->key[i - 1] = Brother->key[0];
            }
        }
        return true;
    }
    structure NewKey;
    NewKey.clear();
    if (1 == flag)
    {
        Brother->Merge(p);
        NewKey = p->key[0];
        delete p;
    }
    else
    {
        p->Merge(Brother);
        NewKey = Brother->key[0];
        delete Brother;
    }
    return Remove_Node(parent, NewKey);
}

void Bplus::Print()
{
    Node* p = Root;
    if (NULL == p)
        return;
    Inter_Node* a;
    int H = 0;
    queue<Node*> q;
    queue<int> h;
    q.push(p);
    h.push(1);
    while (!q.empty())
    {
        p = q.front();
        if (H != h.front())
        {
            cout << endl;
            cout << H << endl;
            H = h.front();
        }
        q.pop();
        h.pop();
        p->Print();
        if (NULL != p && !p->isLeaf)
        {
            a = (Inter_Node*)p;
            for (int i = 0; i <= p->count; i++)
            {
                q.push(a->Child[i]);
                h.push(H + 1);
            }
        }
    }
}
