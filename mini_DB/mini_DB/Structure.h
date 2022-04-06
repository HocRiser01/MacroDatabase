#pragma once
#include<vector>
#include"Config.h"
using namespace std;

struct datachunk {//name, ID, year, birthday, college, GPA (string[1..10], int(0..100000000), int(10, 22), int(0, 1231), string[1,10], double(0..4.0)
    bool valid = 0;
    int nI = 0, nD = 0, nS = 0; //number of Int, Double & String
	int Int[Column];
    double Double[Column];
    char String[Column][10];
	datachunk* next;
};
datachunk* data_insert(datachunk*, datachunk& input_a);
int data_size(datachunk*);
datachunk* data_search(datachunk*, int number);

struct datachunk_manager {
	datachunk* position;
	datachunk_manager* next;
};
datachunk_manager* datachunk_insert(datachunk_manager* list, datachunk* data);
int datachunk_size(datachunk_manager* list);
datachunk* datachunk_search(datachunk_manager* list, int number);


struct structure {
	datachunk_manager* pposition;
	int line1;
	double line2;
	char line3[100];
	void operator  = (structure second);
	bool larger_than_second(structure second, int type);
	bool smaller_than_second(structure second, int type);
	bool same_to_second(structure second, int type);
	void clear();
};
