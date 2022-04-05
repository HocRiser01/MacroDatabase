#include"B_plus.h"
#include<iostream>
#include<vector>
using namespace std;

int main() {
	int num;
	cout << "Please insert the num of data:" << endl;
	cin >> num;
	datachunk* t = nullptr;
	cout << "Please insert the number" << endl;
	datachunk mid;
	structure mid2;
	for (int i = 0; i < num; i++) {
		
		cin >> mid.a;
		t = data_insert(t,mid);
	}//read data

	cout << "Search line?" << endl;
	int line;//确定按哪一列建索引
	cin >> line;
	Bplus tree;//建树
	tree.type_of_key = line;
	for (int i = 0; i < num; i++) {
		mid2.clear();
		mid2.pposition = datachunk_insert(mid2.pposition, data_search(t, i));
		if (mid2.pposition == nullptr) {
			return 0;
		}
		//cout << datachunk_size(mid2.pposition) << endl;
		//cout << i << endl;
		mid2.line1 = data_search(t,i)->a;
		tree.Insert(mid2, data_search(t, i));
	}
	cout << "tree has been made." << endl;
	tree.Print();
	cout << endl;
	while (true) {
		cout << "Search what?" << endl;//模拟查找
		int value;
		cin >> value;
		if (line == 1) {//将查找内容转换成索引结构体进行查找
			mid2.line1 = value;
		}
		datachunk_manager* position = tree.Search(mid2);
		if (position != nullptr) {
			int size = datachunk_size(position);
			cout << "Find " << size << "Result(s):" << endl;
			for (int i = 0; i < size; i++) {
				cout << "value " << value << " position is in:" << datachunk_search(position, i) << ",value: " << datachunk_search(position, i)->a << endl;
			}
		}
		else{
			cout << "No data" << endl;
		}
		
		cout << "Delete what?" << endl;//模拟删除
		cin >> value;
		if (line == 1) {
			mid2.line1 = value;
		}
		tree.Delete(mid2);
		//tree.Print();
		cout << "Insert what?" << endl;//模拟插入
		cin >> value;
		mid.a = value;//插入的内容与索引无关
		
		data_insert(t,mid);//插入内容送入vector
		/*
		cout << data_size(t) << " " << data_search(t,data_size(t)-1) << endl;
		for (int i = 0; i < data_size(t); i++) {
			cout << data_search(t, i) << "\t";
		}
		cout << endl;
		for (int i = 0; i < data_size(t); i++) {
			cout << data_search(t, i)->a << "\t";
		}
		cout << endl;
		*/
		//但需要将插入的内容变为结构体
		int i = data_size(t);
		mid2.clear();
		mid2.line1 = data_search(t,i - 1)->a;
		mid2.pposition = datachunk_insert(mid2.pposition, data_search(t, i - 1));
		tree.Insert(mid2, data_search(t, i - 1));
		tree.Print();
		cout << endl;
	}
}