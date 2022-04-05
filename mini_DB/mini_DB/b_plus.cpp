#include "B_plus.h"
#include<iostream>
#include<queue>
#include<vector>
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
        int k = i > 0 ? i - 1 : i;
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

bool Bplus::Insert(structure data,datachunk* data_point) //dataΪ����Ĺؼ���
{
    if (nullptr != Search(data)) {//����Ҫ�����ֵ
        //cout << "Already have one!" << endl;
        datachunk_manager* mid_list = Search(data);
        mid_list = datachunk_insert(mid_list, data_point);
        return true;
    }

    Leaf_Node* Old_Node = Find(data);//�ҵ���Ҫ�����Ҷ�ӽڵ㶨��Ϊoldnode

    if (Old_Node == nullptr)
    {
        Old_Node = new Leaf_Node;//��Ϊ��
        Old_Node->type_of_key = type_of_key;
        Root = Old_Node;
    }

    if (Old_Node->count < M * 2) {//�пռ���룬ֱ�Ӳ��ȥ������
        return Old_Node->Insert(data);

    }

    Leaf_Node* New_Node = new Leaf_Node;//��������
    New_Node->type_of_key = type_of_key;

    structure k = Old_Node->Split(New_Node);//kΪ�½ڵ��һ���ؼ���

    Leaf_Node* OldNext = Old_Node->Next_Node;
    Old_Node->Next_Node = New_Node;//����Ҷ�ӽڵ�����
    New_Node->Next_Node = OldNext;
    New_Node->Pre_Node = Old_Node;

    if (OldNext != nullptr)
        OldNext->Pre_Node = New_Node;

    if (data.smaller_than_second(k,type_of_key))//С��newnode key[0]����ǰ�棬��������
    {
        Old_Node->Insert(data);
    }
    else
    {
        New_Node->Insert(data);
    }
    Inter_Node* parent = (Inter_Node*)(Old_Node->Parent);

    if (parent == nullptr)//��ʼ��parent����û�и���㣬�½�һ��
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

    return Add_Node(parent, k, New_Node);//�������ֵ���߷��Ѹ��׽����µĽڵ�
}

bool Bplus::Delete(structure data)
{
    if (Search(data) == nullptr) {
        return false;
    }
    Leaf_Node* Old_Node = Find(data); //��������
    if (Old_Node == nullptr)//��Ϊ��
        return false;
    if (false == Old_Node->Delete(data)) //ɾ��
        return false;
    Inter_Node* parent = (Inter_Node*)(Old_Node->Parent);
    if (parent == nullptr)
    {
        if (0 == Old_Node->count)//��������ɾ����û����ûkey
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
            if (parent->key[i].same_to_second(data,type_of_key))//���Ҫɾ����key�ȸ�����������ֵҪ���ֱ��ɾ���������ȣ��͸�����һ��������
                parent->key[i] = Old_Node->key[0];
        }
        return true;
    }
    //��������Ҫ�ϲ����ֵ
    int flag = 1;
    Leaf_Node* Brother = (Leaf_Node*)(Old_Node->GetBrother(flag));
    structure NewData;
    NewData.clear();
    if (Brother->count > M)//��ֵ
    {
        if (1 == flag)//���ֵ�
        {
            NewData = Brother->key[Brother->count - 1];//Ҫ�����ߵ�����
        }
        else//���ֵ�
        {
            NewData = Brother->key[0];
        }
        Old_Node->Insert(NewData);
        Brother->Delete(NewData);
        //�滻parent�е�keyֵ
        if (1 == flag)
        {
            for (int i = 0; i <= parent->count; i++)//�����ֵܽ�ֵ
            {
                if (parent->Child[i] == Old_Node && i > 0)
                    parent->key[i - 1] = Old_Node->key[0];
            }
        }
        else
        {
            for (int i = 0; i <= parent->count; i++)//�����ֵܽ�ֵ
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
    if (1 == flag)//�޷���ֵ���ϲ�
    {
        Brother->Merge(Old_Node);
        NewKey = Old_Node->key[0];//���Ҫɾ���ĸ������key
        Leaf_Node* OldNext = Old_Node->Next_Node;//��������ֵ�
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
    return Remove_Node(parent, NewKey);//�Ƴ�parent�����Ƴ�parent�йؼ��֣�
}

Leaf_Node* Bplus::Find(structure data)//dataΪ�ؼ���
{
    int i = 0;
    Node* p = Root; //?????bplus�ĸ�
    Inter_Node* q;  //?��???
    while (p != nullptr)
    {
        if (p->isLeaf) //????????????
            break;
        for (i = 0; i < p->count; i++) //??????p??key?????p����Ҷ�ӣ�ѭ����count�Ľڵ�
        {
            if (data.smaller_than_second(p->key[i],type_of_key))
                break;
        }
        q = (Inter_Node*)p;
        p = q->Child[i];
    }

    return (Leaf_Node*)p;//�Ѹ�return,�����Ϊ��,��һ�����뺯�����ɵĽڵ㼴Ϊ��
}

bool Bplus::Add_Node(Inter_Node* p, structure k, Node* New_Node)
{
    if (p == nullptr || p->isLeaf)
        return false;
    if (p->count < M * 2)//���ײ���
        return p->Insert(k, New_Node);
    Inter_Node* Brother = new Inter_Node;
    Brother->type_of_key = type_of_key;
    //Ҷ�ӽڵ��������ڵ�Ҳ���������
    structure NewKey = p->Split(Brother, k);//NewKeyΪ��Ҫ��ȡ�����뵽root�ڵ��ֵ

    //ȷ����Ҫ����Ĺؼ��֣��ǲ��뵽���ѽڵ���ĸ�λ��
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
        parent->key[0] = NewKey;//newkeyΪ���Ѵ��أ�Ϊ������м�ֵ
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
    if (p->count >= M)//���ײ��ϲ�
    {
        //ɾ��parent�еĹؼ���
        for (int i = 0; (i < parent->count) && (parent->key[i].smaller_than_second(k, type_of_key) || parent->key[i].same_to_second(k, type_of_key)); i++)
        {
            if (parent->key[i].same_to_second(k,type_of_key))//�����׵�parent����û��Ҫɾ���Ĺؼ��֣��о͸�������
                parent->key[i] = p->key[0];
        }
        return true;
    }
    //���׺ϲ�
    int flag = 1;
    Inter_Node* Brother = (Inter_Node*)(p->GetBrother(flag));
    if (Brother->count > M)//���׽�ֵ
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
    //�ֵܽ�ֵ
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