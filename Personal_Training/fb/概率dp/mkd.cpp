
#include <bits/stdc++.h>
#define N 301000
using namespace std;
double l,ans;
char s[N], a[] = {'o', 'x', '?'};
int n;
int main()
{
  freopen("a.in","w",stdout);
    int i,j,k;
    srand(time(0));
	n = 300000;
    cout <<  n << endl;
    for(i=1;i<=n;i++) {
		int p = rand() % 3;
		//int p = 2;
		cout << a[p];
	}
    return 0;
}
