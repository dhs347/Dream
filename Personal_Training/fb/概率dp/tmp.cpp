
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#define N 301000
using namespace std;
double l,ans;
char s[N];
int n;
int main()
{
  freopen("a.in","r",stdin);
    int i,j,k;
    scanf("%d%s",&n,s+1);
    for(i=1;i<=n;i++)
    {
        if(s[i]=='x')l=0;
        else if(s[i]=='o')ans+=(++l)*2-1;
        else ans+=(l*2+1)*0.5,l=(l+1)*0.5;
    }
    printf("%.4lf\n",ans);
 
    return 0;
}
