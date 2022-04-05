#include"InterNode.h"

Inter_Node::Inter_Node()
{
    isLeaf = false;
    for (int i = 0; i < M * 2 + 1; i++)
        Child[i] = nullptr;
}

Inter_Node::~Inter_Node()
{
    for (int i = 0; i < M * 2 + 1; i++)
        Child[i] = nullptr;
}

bool Inter_Node::Insert(structure value, Node* New)
{
    int i = 0;
    for (; (i < count) && (value.larger_than_second(key[i],type_of_key)); i++)//i指向key要插入的位置
    {
    }
    for (int j = count; j > i; j--)//挪动倒地方
        key[j] = key[j - 1];
    for (int j = count + 1; j > i + 1; j--)//父亲key值改变，孩子移动；
        Child[j] = Child[j - 1];
    key[i] = value;//关键字传到父亲节点
    Child[i + 1] = New;//newnode放到该放的位置
    New->Parent = this;
    count++;
    return true;
}

bool Inter_Node::Delete(structure k)
{
    int i = 0;
    for (; !(k.smaller_than_second(key[i],type_of_key)) && (i < count); i++)
    {
    }
    for (int j = i - 1; j < count - 1; j++)
        key[j] = key[j + 1];
    int j = i;
    for (; j < count; j++)
    {
        Child[j] = Child[j + 1];
    }
    Child[j] = nullptr;
    count--;
    return true;
}

structure Inter_Node::Split(Inter_Node* p, structure k)
{
    int i = 0, j = 0;
    if ((k.larger_than_second(this->key[M - 1], type_of_key)) && (k.smaller_than_second(this->key[M], type_of_key)))//分裂的地方在中间
    {
        for (i = M; i < M * 2; i++, j++)
            p->key[j] = this->key[i];//拷贝后面值进brother
        j = 1;
        for (i = M + 1; i <= M * 2; i++, j++)
        {
            this->Child[i]->Parent = p;//孩子跟着往后移动
            p->Child[j] = this->Child[i];
        }
        this->count = M;//关键子数量各位一半
        p->count = M;
        return k;
    }
    int pos = k.smaller_than_second(this->key[M - 1],type_of_key) ? (M - 1) : M;//看k大小和中间-1比较，定位在前面还是在后面节点
    k = this->key[pos];//pos为分裂点,定位为前还是后分裂点,最后肯定为中间值
    j = 0;
    for (i = pos + 1; i < M * 2; i++, j++)//前节点考后节点,从插入的位置分，插入以后的放到新节点
        p->key[j] = this->key[i];
    j = 0;
    for (i = pos + 1; i <= M * 2; i++, j++)//将孩子送给兄弟
    {
        this->Child[i]->Parent = p;
        p->Child[j] = this->Child[i];
    }
    this->count = pos;
    p->count = M * 2 - pos - 1;
    return k;
}

bool Inter_Node::Merge(Inter_Node* p)
{
    key[count] = p->Child[0]->key[0];
    count++;
    Child[count] = p->Child[0];
    for (int i = 0; i < p->count; i++)
    {
        key[count] = p->key[i];
        count++;
        Child[count] = p->Child[i + 1];
    }
    return true;
}

bool Inter_Node::Slib(Inter_Node* p)
{
    int i, j;
    if (p->key[0].smaller_than_second(this->key[0],type_of_key))
    {
        for (i = count; i > 0; i--)
            key[i] = key[i - 1];
        for (j = count + 1; j > 0; j--)
            Child[j] = Child[j - 1];
        key[0] = Child[0]->key[0];
        Child[0] = p->Child[p->count];
    }
    else
    {
        key[count] = p->Child[0]->key[0];
        Child[count + 1] = p->Child[0];
        for (i = 1; i < p->count - 1; i++)
            p->key[i - 1] = p->key[i];
        for (j = 0; j < p->count - 1; j++)
            p->Child[j] = p->Child[j + 1];
    }
    this->count++;
    p->count--;
    return true;
}

