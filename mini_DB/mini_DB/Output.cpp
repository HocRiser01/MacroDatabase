#include<iostream>
#include"Config.h"
#include"Shared.h"
#include"B_plus.h"
using namespace std;

void Print(datachunk &a){
    int cI = 0, cD = 0, cS = 0;
    for (int i = 1; i <= column; ++ i){
        if (Type[i] == '1') cout << a.Int[cI ++] << ' ';
        if (Type[i] == '2') cout << a.Double[cD ++] << ' ';
        if (Type[i] == '3') cout << a.String[cS ++] << ' ';
    }
    cout << endl;
}
