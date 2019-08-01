#include<bits/stdc++.h>
using namespace std;
const int MAXN=500000+10;
int T,n,m,op,l,r,tmp,ans,a[MAXN],f[MAXN][32],pos[MAXN][32];
inline int Read() 
{
    int x=0,f=1; char ch=getchar(); 
    while (ch<'0'||ch>'9') {if (ch=='-') f=-f; ch=getchar();}
    while (ch>='0'&&ch<='9') x=x*10+ch-'0',ch=getchar();
    return x*f;
}
char s[30];
inline void writeln(int x)
{
	if (x<0) putchar('-'),x=-x; 
	if (!x) putchar('0'); else 
	{
	    int len=0;  
	    while (x) s[++len]=x%10+'0',x/=10;
	  	while (len) putchar(s[len--]);
	} 
	putchar('\n');
}
inline void Add(int i,int x)
{
	int k=i;
	for (int j=30;j>=0;--j) f[i][j]=f[i-1][j],pos[i][j]=pos[i-1][j];
	for (int j=30;j>=0;--j) if (x>>j)
	{
		if (!f[i][j]) 
		{
			f[i][j]=x;
			pos[i][j]=k;
			break;
		}
		else 
		{
			if (k>pos[i][j]) 
			{
				tmp=k,k=pos[i][j],pos[i][j]=tmp;
				tmp=x,x=f[i][j],f[i][j]=tmp;
			}
            x^=f[i][j];
		}
	}
}
int main()
{
	//freopen("test.in","r",stdin);
	//freopen("test.out","w",stdout);
	T=Read();
	while (T--)
	{
		n=Read(),m=Read();
		for (int i=1;i<=n;++i) a[i]=Read(),Add(i,a[i]);
		ans=0;
	    while (m--)
	    {
	    	op=Read();
	    	if (op) a[++n]=Read()^ans,Add(n,a[n]);
			else
			{
				l=Read(),r=Read();
				l=(l^ans)%n+1,r=(r^ans)%n+1;
				if (l>r) swap(l,r);
                ans=0;
                for (int j=30;j>=0;--j) if((ans^f[r][j])>ans&&pos[r][j]>=l) ans^=f[r][j];
                writeln(ans);
			}
		}
		for (int i=1;i<=n;++i)
		  for (int j=30;j>=0;--j) f[i][j]=pos[i][j]=0;
	}
	return 0;
}
