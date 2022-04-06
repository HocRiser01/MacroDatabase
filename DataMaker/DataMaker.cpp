#include<cstdio>
#include<cstring>
#include<iostream>
#include<algorithm>
using namespace std;

int main(){
	int n, m;
    char Type[1000];
    double llim[1000], rlim[30];
    cout << "Please enter the number of rows and columns in the database" << endl;
    cin >> n >> m;
	cout << "Please enter the data type of each field" << endl;
	cout << "1 for Int, 2 for Double and 3 for String" << endl;
	cout << "Example: 3 1 1 1 3 2" << endl;
	for (int i = 1; i <= m; ++ i){
		cout << "column:" << i << endl;
		scanf(" %c", Type + i);
		if (Type[i] == '1'){
			cout << "Please enter the range of this colume, e.g. 1 100" << endl;
			cin >> llim[i] >> rlim[i];
		}else if (Type[i] == '2'){
			cout << "Please enter the range of this colume, e.g. 1.14 5.14" << endl;
			cin >> llim[i] >> rlim[i];
		}else if (Type[i] == '3'){
			cout << "String, ok, nothing need to be entered" << endl;
		}
	}
	freopen("DataBase.dat","w",stdout);
	for (int i = 1; i <= n; ++ i){
		for (int j = 1; j <= m; ++ j){
			if (Type[j] == '1')
				printf("%d ", (int)(random() % (int)(rlim[j] - llim[j] + 1) + llim[j]));
			if (Type[j] == '2')
				printf("%.2lf ", random() % (int)((rlim[j] - llim[j])*100 + 1) / 100. + llim[j]);
			if (Type[j] == '3'){
				int len = random() % 10 + 1;
				for (int k = 1; k <= len; ++ k)
					putchar((char)(random() % 26 + 'a'));
				putchar(' ');
			}
		}
		puts("");
	}
	return 0;
}