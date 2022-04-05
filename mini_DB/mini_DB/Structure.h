#pragma once
#include<vector>
using namespace std;
struct datachunk {
	int a;
	datachunk* next;
};//�����ݵĽṹ�壬���ϸ��汾��vector����������
datachunk* data_insert(datachunk*, datachunk& input_a);
int data_size(datachunk*);
datachunk* data_search(datachunk*, int number);//���ݵļ򵥲��롢�жϴ�С�Ͳ���

struct datachunk_manager {
	datachunk* position;
	datachunk_manager* next;

};//�������ݵĽṹ�壬������structure�У������ȡͬһ�ֶ��¶������
datachunk_manager* datachunk_insert(datachunk_manager* list, datachunk* data);
int datachunk_size(datachunk_manager* list);
datachunk* datachunk_search(datachunk_manager* list, int number);//���ݹ������ļ򵥲��롢�жϴ�С�Ͳ��ҡ�


struct structure {
	//int position;//��vector���ǵڼ���Ԫ�أ���0��ʼ
	datachunk_manager* pposition;//��ŵ�ַ
	int line1;//�������
	double line2;//��Ÿ�����
	char line3[100];//����ַ�����
	void operator  = (structure second);//��ֵ
	bool larger_than_second(structure second, int type);//�Ƚϵ���������
	bool smaller_than_second(structure second, int type);
	bool same_to_second(structure second, int type);
	void clear();//���û��ʼ��
};

