#include<cstdio>
#include<cstring>
#include<iostream>
#include"B_plus.h"
#include"Shared.h"
#include"Help.h"
#include"Panel.h"
#include"Config.h"
#include"System.h"
#include"Operations.h"
using namespace std;

int main() {
    char FILE_NAME[100] = {0};
    cls();
    cout << "--- Welcome to mini_DB DataBase Manager ---" << endl;
    cout << "Please enter the number of rows [1, 10000000]" << endl;
    while (1){
        cin >> row;
        if (row < 1 || row > 10000000)
            cout << "Invalid number [1, 10000000]" << endl;
        else break;
    }
    cout << "Please enter the data type of each field" << endl;
    cout << "1 for Int, 2 for Double and 3 for String" << endl;
    cout << "Example: 3 1 1 1 3 2" << endl;
    while (1){
        bool success = 1;
        char ch;
        ch = getchar();
        while (1){
            ch = getchar();
            if (ch == '\n') break;
            if (ch == ' ') continue;
            if (ch < '1' || ch > '3'){
                cout << "Please enter the right number" << endl;
                while (ch != '\n') ch=getchar();
                success = 0;
                column = 0;
                break;
            }
            Type[++ column] = ch;
        }
        if (success) break;
    }
    for (int i = 1; i <= column; ++ i) cout << Type[i] << ' ';
    cout << endl;
    cout << "Please enter the column which is the main key" << endl;
    while (1){
        cin >> key;
        if (key < 1 || key > column){
            cout << "Please enter the right number" << endl;
        }else break;
    }
    ttype = Type[key];
    cout << "Please enter the actual address of the file" << endl;
//    cin >> FILE_NAME;
    strcpy(FILE_NAME, "DataBase.dat");
    freopen(FILE_NAME, "r", stdin);
    cout << "Loading Database..." << endl;
    tree.type_of_key = ttype - '0';
    for (int i = 1; i <= row; ++ i) Insertrow();
    cout << "Loading Complete" << endl;
    Closefile();
    ShowHelp(); cls(); Panel();
    return 0;
}
