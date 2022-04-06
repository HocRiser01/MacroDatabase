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
    int line;
    cin >> line;
    Bplus tree;
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
        cout << "Search what?" << endl;
        int value;
        cin >> value;
        if (line == 1) {
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
        
        cout << "Delete what?" << endl;
        cin >> value;
        if (line == 1) {
            mid2.line1 = value;
        }
        tree.Delete(mid2);
        //tree.Print();
        cout << "Insert what?" << endl;
        cin >> value;
        mid.a = value;
        
        data_insert(t,mid);
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
        int i = data_size(t);
        mid2.clear();
        mid2.line1 = data_search(t,i - 1)->a;
        mid2.pposition = datachunk_insert(mid2.pposition, data_search(t, i - 1));
        tree.Insert(mid2, data_search(t, i - 1));
        tree.Print();
        cout << endl;
    }
}
