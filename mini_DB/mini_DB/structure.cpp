#include"Structure.h"
#include<iostream>
using namespace std;

datachunk* data_insert(datachunk* list, datachunk& input) {
	datachunk* first_node = list;
	if (list == nullptr) {
		//cout << "null" << endl;
		list = new datachunk;
		list->a = input.a;
		list->next = nullptr;
		return list;
	}
	while (first_node->next != nullptr) {
		first_node = first_node->next;
	}
	datachunk* second_node = new datachunk;
	first_node->next = second_node;
	second_node->a = input.a;
	second_node->next = nullptr;
	return list;
}
int data_size(datachunk* list) {
	datachunk* first_node = list;
	int number = 0;
	while (first_node != nullptr) {
		first_node = first_node->next;
		number++;
	}
	return number;
}
datachunk* data_search(datachunk* list, int number) {
	datachunk* first_node = list;
	for (int i = 0; i < number && first_node != nullptr; i++) {
		first_node = first_node->next;
	}
	if (first_node == nullptr) {
		return nullptr;
	}
	else {
		return first_node;
	}
}

datachunk_manager* datachunk_insert(datachunk_manager* list, datachunk* data){
	datachunk_manager* first_node = list;
	if (list == nullptr) {
		//cout << "null" << endl;
		list = new datachunk_manager;
		list->position = data;
		list->next = nullptr;
		return list;
	}
	while (first_node->next != nullptr) {
		first_node = first_node->next;
	}
	datachunk_manager* second_node = new datachunk_manager;
	first_node->next = second_node;
	second_node->position = data;
	second_node->next = nullptr;
	return list;
}

int datachunk_size(datachunk_manager* list) {
	datachunk_manager* first_node = list;
	int number = 0;
	while (first_node != nullptr) {
		first_node = first_node->next;
		number++;
	}
	return number;
}

datachunk* datachunk_search(datachunk_manager* list, int number) {
	datachunk_manager* first_node = list;
	for (int i = 0; i < number && first_node != nullptr; i++) {
		first_node = first_node->next;
	}
	if (first_node == nullptr) {
		return nullptr;
	}
	else {
		return first_node->position;
	}
}

void structure::operator = (structure second) {
	this->pposition = second.pposition;
	this->line1 = second.line1;
	this->line2 = second.line2;
	for (int i = 0; i < 100; i++) {
		this->line3[i] = second.line3[i];
	}
}

bool structure::larger_than_second(structure second, int type) {
	if (type == 1) {
		if (line1 > second.line1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == 2) {
		if (line2 > second.line2) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == 3) {
		for (int i = 0; i < 100; i++){
			if (line3[i] > second.line3[i]) {
				return true;
			}
		}
		return false;
	}
}

bool structure::smaller_than_second(structure second, int type) {
	if (type == 1) {
		if (line1 < second.line1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == 2) {
		if (line2 < second.line2) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == 3) {
		for (int i = 0; i < 100; i++) {
			if (line3[i] < second.line3[i]) {
				return true;
			}
		}
		return false;
	}
}

bool structure::same_to_second(structure second, int type) {
	if (type == 1) {
		if (line1 == second.line1) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == 2) {
		if (line2 == second.line2) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (type == 3) {
		for (int i = 0; i < 100; i++) {
			if (line3[i] != second.line3[i]) {
				return false;
			}
		}
		return true;
	}
}

void structure::clear() {
	//position = 0;
	pposition = nullptr;
	line1 = 0;
	line2 = 0;
	for (int i = 0; i < 100; i++) {
		line3[i] = 0;
	}
}