#include<iostream>
#include"Help.h"
#include"System.h"
using namespace std;

void ShowHelp(){
    cout << "--- Help for mini_DB ---" << endl;
    cout << "Enter:'head' to show the first 10 rows" << endl;
    cout << "Enter:'size' to show the number of rows" << endl;
    cout << "Enter:'insert' to insert a row, followed with a complete row in the next line" << endl;
    cout << "Enter:'delete' to delete all the row with the same main key" << endl;
    cout << "Enter:'search' to search all the row with the same main key" << endl;
    cout << "Enter:'help' to get this help manual again" << endl;
    cout << "You'll have a guide when you operate" << endl;
    cout << "Produced By HJZ, YJL & WX from TAQ class, JLU, April 2022" << endl;
    cout << endl;
    cout << "Press any key to continue" << endl;
    pause();
}
