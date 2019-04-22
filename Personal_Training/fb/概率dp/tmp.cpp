#include<iostream>
#include<cstdio>
#define N 500005
using namespace std;
int n,cnt;
int head[N];
int list[N<<1],next[N<<1];
double key[N<<1];
double f[N][2];
double h[N];
inline int read()
{
    int a=0,f=1; char c=getchar();
    while (c<'0'||c>'9') {if (c=='-') f=-1; c=getchar();}
    while (c>='0'&&c<='9') {a=a*10+c-'0'; c=getchar();}
    return a*f;
}
inline void insert(int x,int y,double z)
{
    next[++cnt]=head[x];
    head[x]=cnt;
    list[cnt]=y;
    key[cnt]=z;
}
void dfs(int x,int fa)
{
    for (int i=head[x];i;i=next[i])
        if (list[i]!=fa)
        {
            dfs(list[i],x);
            h[list[i]]=f[list[i]][0]+(1-f[list[i]][0])*(1-key[i]);
            f[x][0]*=h[list[i]];
        }
}
void dfs1(int x,int fa)
{
    for (int i=head[x];i;i=next[i])
        if (list[i]!=fa)
        {
            double t=h[list[i]]<1e-6?0:f[x][1]*f[x][0]/h[list[i]];
            f[list[i]][1]=t+(1-t)*(1-key[i]);
            dfs1(list[i],x);
        }
}
int main()
{
	freopen("a.in", "r", stdin);
    n=read(); 
    for (int i=1;i<n;i++)
    {
        int u=read(),v=read(),w=read();
        insert(u,v,w/100.0); insert(v,u,w/100.0);
    }
    for (int i=1;i<=n;i++)
    {
        int x=read();
        f[i][0]=1-x/100.0;
    }
    dfs(1,0);
    f[1][1]=1;
    dfs1(1,0);
    double ans=0;
    for (int i=1;i<=n;i++)
        ans+=1-f[i][0]*f[i][1];
    printf("%.6lf",h[2]);
    return 0;
}

