#include<iostream>
#include"Shared.h"
#include"B_plus.h"
#include"Operations.h"
using namespace std;

void Insertrow(){
    int tn = 0;
    char ch;
    datachunk Tmp;
    for (int j = 1; j <= column; ++ j){
        if (Type[j] == '1'){
            cin >> Tmp.Int[Tmp.nI ++];
            if (j < column) getchar();
        }else if (Type[j] == '2'){
            cin >> Tmp.Double[Tmp.nD ++];
            if (j < column) getchar();
        }else if (Type[j] == '3'){
            ++ Tmp.nS;
            int len = 0;
            while ((ch = getchar()) != ',' && ch != ' ')
                Tmp.String[Tmp.nS][len ++] = ch;
            Tmp.String[Tmp.nS][len] = 0;
        }
        if (j == key){
            tn = (Type[j] == '1') ? Tmp.nI - 1 : (Type[j] == '2') ? Tmp.nD - 1 : Tmp.nS - 1;
        }
    }
    /*
    for (int i = 0; i < Tmp.nI; ++ i) cout << Tmp.Int[i] << ' ';
    cout << endl;
    for (int i = 0; i < Tmp.nD; ++ i) cout << Tmp.Double[i] << ' ';
    cout << endl;
    for (int i = 0; i < Tmp.nS; ++ i) cout << Tmp.String[i] << ' ';
    cout << endl;
    */
    my_list[++ size] = new datachunk(Tmp);
    d_list = data_insert(d_list, *my_list[size]);
    structure mainkey;
    if (ttype == '1'){
        mainkey.line1 = Tmp.Int[tn];
//        cout << mainkey.line1 << endl;
    }else if (ttype == '2'){
        mainkey.line2 = Tmp.Double[tn];
//        cout << mainkey.line2 << endl;
    }else if (ttype == '3'){
        strcpy(mainkey.line3, Tmp.String[tn]);
//        cout << mainkey.line3 << endl;
    }
    tree.Insert(mainkey, my_list[size]);
}

void Deletekey(){
    if (ttype == '1'){
        int key;
        cin >> key;
        structure mainkey;
        mainkey.line1 = key;
        datachunk_manager *s = tree.Search(mainkey);
        if (!s){
            cout << "No eligible members" << endl;
        }else{
            int cnt = 0;
            while (s){
                if (!s -> position -> valid){
                    ++ cnt; -- size;
                    s -> position -> valid = 1;
                }
                s = s->next;
            }
            if (!cnt) cout << "No eligible members" << endl;
            else cout << cnt << " members deleted" << endl;
        }
    }else if (ttype == '2'){
        double key;
        cin >> key;
        structure mainkey;
        mainkey.line2 = key;
        datachunk_manager *s = tree.Search(mainkey);
        if (!s){
            cout << "No eligible members" << endl;
        }else{
            int cnt = 0;
            while (s){
                if (!s -> position -> valid){
                    ++ cnt; -- size;
                    s -> position -> valid = 1;
                }
                s = s->next;
            }
            if (!cnt) cout << "No eligible members" << endl;
            else cout << cnt << " members deleted" << endl;
        }
    }else if (ttype == '3'){
        char key[10];
        cin >> key;
        structure mainkey;
        strcpy(mainkey.line3, key);
        datachunk_manager *s = tree.Search(mainkey);
        if (!s){
            cout << "No eligible members" << endl;
        }else{
            int cnt = 0;
            while (s){
                if (!s -> position -> valid){
                    ++ cnt; -- size;
                    s -> position -> valid = 1;
                }
                s = s->next;
            }
            if (!cnt) cout << "No eligible members" << endl;
            else cout << cnt << " members deleted" << endl;
        }
    }
}
