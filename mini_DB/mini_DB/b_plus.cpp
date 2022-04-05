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

bool Bplus::Insert(structure data,datachunk* data_point) //data为插入的关键字
{
    if (nullptr != Search(data)) {//查找要插入的值
        //cout << "Already have one!" << endl;
        datachunk_manager* mid_list = Search(data);
        mid_list = datachunk_insert(mid_list, data_point);
        return true;
    }

    Leaf_Node* Old_Node = Find(data);//找到需要插入的叶子节点定义为oldnode

    if (Old_Node == nullptr)
    {
        Old_Node = new Leaf_Node;//树为空
        Old_Node->type_of_key = type_of_key;
        Root = Old_Node;
    }

    if (Old_Node->count < M * 2) {//有空间插入，直接插进去并返回
        return Old_Node->Insert(data);

    }

    Leaf_Node* New_Node = new Leaf_Node;//即将分裂
    New_Node->type_of_key = type_of_key;

    structure k = Old_Node->Split(New_Node);//k为新节点第一个关键子

    Leaf_Node* OldNext = Old_Node->Next_Node;
    Old_Node->Next_Node = New_Node;//相邻叶子节点相连
    New_Node->Next_Node = OldNext;
    New_Node->Pre_Node = Old_Node;

    if (OldNext != nullptr)
        OldNext->Pre_Node = New_Node;

    if (data.smaller_than_second(k,type_of_key))//小于newnode key[0]，插前面，否则插后面
    {
        Old_Node->Insert(data);
    }
    else
    {
        New_Node->Insert(data);
    }
    Inter_Node* parent = (Inter_Node*)(Old_Node->Parent);

    if (parent == nullptr)//初始化parent，若没有父结点，新建一个
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

    return Add_Node(parent, k, New_Node);//向父亲里插值或者分裂父亲建立新的节点
}

bool Bplus::Delete(structure data)
{
    if (Search(data) == nullptr) {
        return false;
    }
    Leaf_Node* Old_Node = Find(data); //查找数据
    if (Old_Node == nullptr)//树为空
        return false;
    if (false == Old_Node->Delete(data)) //删除
        return false;
    Inter_Node* parent = (Inter_Node*)(Old_Node->Parent);
    if (parent == nullptr)
    {
        if (0 == Old_Node->count)//将整棵树删掉，没父亲没key
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
            if (parent->key[i].same_to_second(data,type_of_key))//如果要删除的key比父亲索引他的值要大就直接删除，如果相等，就给父亲一个新索引
                parent->key[i] = Old_Node->key[0];
        }
        return true;
    }
    //不满足规格，要合并或借值
    int flag = 1;
    Leaf_Node* Brother = (Leaf_Node*)(Old_Node->GetBrother(flag));
    structure NewData;
    NewData.clear();
    if (Brother->count > M)//借值
    {
        if (1 == flag)//左兄弟
        {
            NewData = Brother->key[Brother->count - 1];//要被借走的数据
        }
        else//右兄弟
        {
            NewData = Brother->key[0];
        }
        Old_Node->Insert(NewData);
        Brother->Delete(NewData);
        //替换parent中的key值
        if (1 == flag)
        {
            for (int i = 0; i <= parent->count; i++)//向左兄弟借值
            {
                if (parent->Child[i] == Old_Node && i > 0)
                    parent->key[i - 1] = Old_Node->key[0];
            }
        }
        else
        {
            for (int i = 0; i <= parent->count; i++)//向右兄弟借值
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
    if (1 == flag)//无法借值，合并
    {
        Brother->Merge(Old_Node);
        NewKey = Old_Node->key[0];//标记要删除的父亲里的key
        Leaf_Node* OldNext = Old_Node->Next_Node;//接入后面兄弟
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
    return Remove_Node(parent, NewKey);//移除parent或者移除parent中关键字；
}

Leaf_Node* Bplus::Find(structure data)//data为关键字
{
    int i = 0;
    Node* p = Root; //?????bplus的跟
    Inter_Node* q;  //?м???
    while (p != nullptr)
    {
        if (p->isLeaf) //????????????
            break;
        for (i = 0; i < p->count; i++) //??????p??key?????p不是叶子，循环至count的节点
        {
            if (data.smaller_than_second(p->key[i],type_of_key))
                break;
        }
        q = (Inter_Node*)p;
        p = q->Child[i];
    }

    return (Leaf_Node*)p;//把根return,如果跟为空,第一个插入函数生成的节点即为根
}

bool Bplus::Add_Node(Inter_Node* p, structure k, Node* New_Node)
{
    if (p == nullptr || p->isLeaf)
        return false;
    if (p->count < M * 2)//父亲不满
        return p->Insert(k, New_Node);
    Inter_Node* Brother = new Inter_Node;
    Brother->type_of_key = type_of_key;
    //叶子节点满，父节点也满分裂情况
    structure NewKey = p->Split(Brother, k);//NewKey为需要提取并插入到root节点的值

    //确定需要插入的关键字，是插入到分裂节点的哪个位置
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
        parent->key[0] = NewKey;//newkey为分裂传回，为插入的中间值
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
    if (p->count >= M)//父亲不合并
    {
        //删掉parent中的关键字
        for (int i = 0; (i < parent->count) && (parent->key[i].smaller_than_second(k, type_of_key) || parent->key[i].same_to_second(k, type_of_key)); i++)
        {
            if (parent->key[i].same_to_second(k,type_of_key))//看父亲的parent里有没有要删除的关键字，有就更新索引
                parent->key[i] = p->key[0];
        }
        return true;
    }
    //父亲合并
    int flag = 1;
    Inter_Node* Brother = (Inter_Node*)(p->GetBrother(flag));
    if (Brother->count > M)//父亲借值
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
    //兄弟借值
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