#pragma once
#include<vector>
using namespace std;
struct datachunk {
	int a;
	datachunk* next;
};//存数据的结构体，将上个版本的vector换成了链表
datachunk* data_insert(datachunk*, datachunk& input_a);
int data_size(datachunk*);
datachunk* data_search(datachunk*, int number);//数据的简单插入、判断大小和查找

struct datachunk_manager {
	datachunk* position;
	datachunk_manager* next;

};//管理数据的结构体，出现在structure中，方便调取同一字段下多个数据
datachunk_manager* datachunk_insert(datachunk_manager* list, datachunk* data);
int datachunk_size(datachunk_manager* list);
datachunk* datachunk_search(datachunk_manager* list, int number);//数据管理器的简单插入、判断大小和查找。


struct structure {
	//int position;//在vector中是第几个元素，从0开始
	datachunk_manager* pposition;//存放地址
	int line1;//存放整型
	double line2;//存放浮点型
	char line3[100];//存放字符串型
	void operator  = (structure second);//赋值
	bool larger_than_second(structure second, int type);//比较的三个函数
	bool smaller_than_second(structure second, int type);
	bool same_to_second(structure second, int type);
	void clear();//重置或初始化
};

