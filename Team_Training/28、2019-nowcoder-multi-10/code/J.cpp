#include <bits/stdc++.h>
using namespace std;

typedef long long LL;

const int MAXN=5005;

struct plank
{
	int w,h;
}a[MAXN];

int n,now;
LL area[MAXN],wd[MAXN],dp[2][MAXN];

bool cmp(const plank &x,const plank &y)
{
	return x.h<y.h;
}

inline LL cal(int l,int r)
{
	return area[r]-area[l-1]-(LL)a[l].h*(wd[r]-wd[l-1]);
}

void solve(int l,int r,int al,int ar)
{
	if (l>r)
		return;
	int m=l+r>>1,p;
	LL &ret=dp[now][m];
	ret=LLONG_MAX;
	for (int i=al;i<=ar&&i<=m;i++)
	{
		LL t=dp[now^1][i-1]+cal(i,m);
		if (t<ret)
		{
			ret=t;
			p=i;
		}
	}
	solve(l,m-1,al,p);
	solve(m+1,r,p,ar);
}

int main()
{
	#ifdef local
		freopen("read.txt","r",stdin);
	#endif
	int k;
	scanf("%d%d",&n,&k);
	for (int i=1;i<=n;i++)
		scanf("%d%d",&a[i].w,&a[i].h);
	sort(a+1,a+n+1,cmp);
	for (int i=1;i<=n;i++)
	{
		area[i]=area[i-1]+(LL)a[i].w*a[i].h;
		wd[i]=wd[i-1]+a[i].w;
	}
	for (int i=1;i<=n;i++)
		dp[0][i]=cal(1,i);
	now=1;
	for (int i=2;i<=k;i++,now^=1)
		solve(1,n,1,n);
	printf("%lld\n",dp[now^1][n]);
	return 0;
}
