#include<cstring>
#include<iostream>
#include"Shared.h"
#include"Output.h"
#include"Config.h"
#include"System.h"
#include"Help.h"
#include"B_plus.h"
#include"Operations.h"
using namespace std;

void Panel(){
    char Opt[100];
    while (1){
        cout << "Please enter your operation" << endl;
        cout << "Enter 'quit' to exit" << endl;
        cin >> Opt;
        if (!strcmp(Opt, "insert")){
            cout << "Please enter your data" << endl;
            Insertrow();
        }else if (!strcmp(Opt, "delete")){
            cout << "Please enter the main key that you need to delete" << endl;
            Deletekey();
        }else if (!strcmp(Opt, "search")){
            cout << "Please enter your main key" << endl;
            int cnt = 0;
            if (ttype == '1'){
                int key;
                cin >> key;
                structure mainkey;
                mainkey.line1 = key;
                for (datachunk_manager *s = tree.Search(mainkey); s; s = s -> next){
                    if (!s -> position -> valid){
                        Print(* s->position);
                        ++ cnt;
                    }
                }
            }else if (ttype == '2'){
                double key;
                cin >> key;
                structure mainkey;
                mainkey.line2 = key;
                for (datachunk_manager *s = tree.Search(mainkey); s; s = s -> next){
                    if (!s -> position -> valid){
                        Print(* s->position);
                        ++ cnt;
                    }
                }
            }else if (ttype == '3'){
                char key[100];
                cin >> key;
                structure mainkey;
                strcpy(mainkey.line3, key);
                for (datachunk_manager *s = tree.Search(mainkey); s; s = s -> next){
                    if (!s -> position -> valid){
                        Print(* s->position);
                        ++ cnt;
                    }
                }
            }
            if (!cnt) cout << "No eligible members" << endl;
            else cout << cnt << " members found" << endl;
        }else if (!strcmp(Opt, "quit")){
            cout << "Goodbye!" << endl;
            break;
        }else if (!strcmp(Opt, "help")){
            ShowHelp(); cls();
            cout << "Please enter your operation" << endl;
//        }else if (!strcmp(Opt, "head")){
//            int cnt = 0;
//            for (datachunk *s = d_list; s && cnt < 10; s = s -> next)
//                if (!s -> valid){
//                    ++ cnt;
//                    Print(*s);
//                }
        }else if (!strcmp(Opt, "size")){
            cout << "There are " << size << " rows in the database now" << endl;
        }
        else{
            cout << "Please enter the correct operation" << endl;
        }
        cout << "----------------------------------------" << endl;
    }
}
