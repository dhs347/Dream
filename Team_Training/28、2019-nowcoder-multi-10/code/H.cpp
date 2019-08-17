#include <bits/stdc++.h>
using namespace std;

#define pb push_back

typedef long long LL;

int cnt[6];
vector <int> G[6];

void solve()
{
	memset(cnt,0,sizeof(cnt));
	for (int i=0;i<6;i++)
		G[i].clear();
	for (int i=0;i<5;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		u--;
		v--;
		G[u].pb(v);
		G[v].pb(u);
	}
	for (int i=0;i<6;i++)
		cnt[G[i].size()]++;
	int mx=0;
	for (int i=0;i<6;i++)
		mx=max(mx,(int)G[i].size());
	if (mx==2)
		puts("n-hexane");
	else if (mx==4)
		puts("2,2-dimethylbutane");
	else if (cnt[3]==2)
		puts("2,3-dimethylbutane");
	else
	{
		int c=0;
		for (int i=0;i<6;i++)
			if (G[i].size()==3)
			{
				for (int v:G[i])
					if (G[v].size()==1)
						c++;
				break;
			}
		if (c==2)
			puts("2-methylpentane");
		else
			puts("3-methylpentane");
	}
}

int main()
{
	#ifdef local
		freopen("read.txt","r",stdin);
	#endif
	int T;
	scanf("%d",&T);
	while (T--) solve();
	return 0;
}
