//hdu 1754 splay tree
#include<cstdio>  
#include<iostream>  
using namespace std;  
const int mm=222222;  
int i,n,m,num[mm];  
struct splaytree  
{  
    int c[mm][2],p[mm],s[mm],v[mm],m[mm];  
    int id,root;  
    void rotate(int x,int f)  
    {  
        int y=p[x];  
        c[y][!f]=c[x][f];  
        p[c[x][f]]=y;  
        p[x]=p[y];  
        if(p[x])c[p[y]][c[p[y]][1]==y]=x;  
        c[x][f]=y;  
        p[y]=x;  
        updata(y);  
    }  
    void splay(int x,int goal)  
    {  
        while(p[x]!=goal)  
            if(p[p[x]]==goal)rotate(x,c[p[x]][0]==x);  
            else  
            {  
                int y=p[x],f=(c[p[y]][0]==y);  
                if(c[y][f]==x)rotate(x,!f);  
                else rotate(y,f);  
                rotate(x,f);  
            }  
        updata(x);  
        if(!goal)root=x;  
    }  
    void select(int k,int goal)  
    {  
        int x=root;  
        while(s[c[x][0]]!=k)  
        {  
            if(s[c[x][0]]>k)x=c[x][0];  
            else k-=(s[c[x][0]]+1),x=c[x][1];  
        }  
        splay(x,goal);  
    }  
    void make(int &x,int l,int r,int f)  
    {  
        if(l>r)return;  
        int m=(l+r)>>1;  
        newnode(x,num[m]);  
        make(c[x][0],l,m-1,x);  
        make(c[x][1],m+1,r,x);  
        p[x]=f;  
        updata(x);  
    }  
    void newnode(int &x,int a)  
    {  
        x=++id;  
        c[x][0]=c[x][1]=p[x]=0;  
        m[x]=v[x]=a;  
        s[x]=1;  
    }  
    void updata(int x)  
    {  
        s[x]=1+s[c[x][0]]+s[c[x][1]];  
        m[x]=max(v[x],max(m[c[x][0]],m[c[x][1]]));  
    }  
    void prepare()  
    {  
        c[0][0]=c[0][1]=p[0]=0;  
        s[0]=v[0]=m[0]=0;  
        id=root=0;  
        newnode(root,-1);  
        newnode(c[root][1],-1);  
        p[id]=root;  
        s[root]=2;  
        make(c[c[root][1]][0],0,n-1,c[root][1]);  
        updata(c[root][1]);  
        updata(root);  
    }  
    void change()  
    {  
        int a,b;  
        scanf("%d%d",&a,&b);  
        select(a,0);  
        v[root]=b;  
        if(b>m[root])m[root]=b;  
    }  
    void answer()  
    {  
        int a,b;  
        scanf("%d%d",&a,&b);  
        select(a-1,0);  
        select(b+1,root);  
        printf("%d\n",m[c[c[root][1]][0]]);  
    }  
} spt;  
int main()  
{  
    char op[2];  
    while(scanf("%d%d",&n,&m)!=-1)  
    {  
        for(i=0; i<n; ++i)scanf("%d",&num[i]);  
        spt.prepare();  
        while(m--)  
        {  
            scanf("%s",op);  
            if(op[0]=='U')spt.change();  
            else spt.answer();  
        }  
    }  
    return 0;  
}