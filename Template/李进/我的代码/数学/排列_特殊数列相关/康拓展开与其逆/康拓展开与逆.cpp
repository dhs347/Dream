/* 
input 
1 5 
1 2 3 4 5 
1 5 
1 2 3 5 4 
2 5 
1 
1 5 
4 5 3 2 1 
2 5 
95 
Output 
Cantor=0 
Cantor=1 
数列为：1 2 3 5 4 
Cantor=95 
数列为：4 5 3 2 1 
*/  
#include<iostream>  
#include<cstdio>  
#include<string>  
#include<cmath>  
#include<queue>  
#include<stack>  
#include<map>  
#include<cstring>  
#include<algorithm>  
#define rep(i,a,b) for(int i=(a);i<(b);i++)  
#define rev(i,a,b) for(int i=(a);i>=(b);i--)  
#define clr(a,x) memset(a,x,sizeof a)  
#define inf 0x3f3f3f3f  
typedef long long LL;  
using namespace std;  
  
const int mod=1e9 +7;  
const int maxn=2005;  
const int maxm=4005;  
  
int fac[]={1,1,2,6,24,120,720,5040,40320,362880};  
int cantor(int *s,int n)  
{  
    int num=0;  
    for(int i=0;i<n-1;i++)  
    {  
        int tmp=0;  
        for(int j=i+1;j<n;j++)  
            if(s[j]<s[i])tmp++;  
        num+=fac[n-i-1]*tmp;  
    }  
    return num;  
}  
  
void _cantor(int *s,int n,int x)  
{  
    bool tmp[n+1];  
    clr(tmp,0);  
    for(int i=n-1;i>=0;i--)  
    {  
        int k=x/fac[i];x%=fac[i];  
        int j=1;  
        for(int sum=0;sum<k||tmp[j];j++)  
            if(!tmp[j])sum++;  
        s[n-1-i]=j;  
        tmp[j]=1;  
    }  
}  
  
int main()  
{  
    int flag,n;  
    while(~scanf("%d%d",&flag,&n))  
    {  
        if(flag==1)  
        {  
            int s[n];  
            for(int i=0;i<n;i++)  
                scanf("%d",&s[i]);  
            printf("Cantor=%d\n",cantor(s,n));  
        }  
        else if(flag==2)  
        {  
            int x,ans[n];  
            scanf("%d",&x);  
            _cantor(ans,n,x);  
            cout<<"数列为：";  
            for(int i=0;i<n;i++)  
                printf("%d%c",ans[i],i==n-1?'\n':' ');  
        }  
    }  
    return 0;  
}  
