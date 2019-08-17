#pragma GCC optimize(3)
#include<bits/stdc++.h>
using namespace std;
const int maxn=100011;
const int N=100000;
map<int,int>mp[maxn];
using BS=bitset<N+10>;
int n,r;
int sx[N+10],sy[N+10];
void init(){
	scanf("%d%d",&n,&r);
	for (int i=1;i<=n;++i){
		int x,y; scanf("%d%d",&x,&y);
		if (x-r>=0){
			if (y-r>=0) mp[x-r][y-r]++;
			mp[x-r][y]++;
			if (y+r<=N) mp[x-r][y+r]++;
		}
		if (y-r>=0) mp[x][y-r]++;
		mp[x][y]++;
		if (y+r<=N) mp[x][y+r]++;
		if (x+r<=N){
			if (y-r>=0) mp[x+r][y-r]++;
			mp[x+r][y]++;
			if (y+r<=N) mp[x+r][y+r]++;
		}
		++sx[x];
		++sy[y];
	}
}
/*
struct LBS{
	vector<int>a;
	bitset<N+10>b;
	bool x;
	const static Lim=200;
	void insert(int x){
		if (!x) a.push_back(x);
		else b.set(x);
		if (a.size()>Lim){
			b.reset();
			for (int x:a) b.set(x);
			a.clear();
			x=1;
		}
	}
	void clear(){
		x=0; a.clear();
	}
}Y[20];*/
BS Y[20];
BS X;
int ssx[N+10],ssy[N+10];
priority_queue<pair<int,int>>q;
int GetMax(int Lim){
	vector<pair<int,int>> d;
	while (!q.empty() && q.top().first>Lim){
		if (X[q.top().second]){
			int ans=q.top().first;
			for (auto &x:d) q.push(x);
			return ans;
		}
		d.emplace_back(q.top()); q.pop();
	}
	for (auto &x:d) q.push(x);
	return Lim;
}
void work(){
	for (int x=0;x<=N;++x){
		ssx[x]=sx[x];
		if (x-r>=0) ssx[x]+=sx[x-r];
		if (x+r<=N) ssx[x]+=sx[x+r];
	}
	for (int y=0;y<=N;++y){
		ssy[y]=sy[y];
		if (y-r>=0) ssy[y]+=sy[y-r];
		if (y+r<=N) ssy[y]+=sy[y+r];
	}
	int mxy=0;
	for (int y=0;y<=N;++y) mxy=max(mxy,ssy[y]);
	for (int y=0;y<=N;++y) q.push(make_pair(ssy[y],y));
	int ans=mxy;
	for (int x=0;x<=N;++x){
		if (ssx[x]+mxy<=ans) continue;
		X.set();
		for (auto &t:mp[x]) X.reset(t.first);
		ans=GetMax(ans-ssx[x])+ssx[x];
		for (int dy=0;dy<=8;++dy){
			if (mxy+ssx[x]-dy>ans)
				if ((X&Y[dy]).count())
					ans=mxy+ssx[x]-dy;
		}
		for (auto &t:mp[x]) ans=max(ans,ssx[x]+ssy[t.first]-t.second);
	}
	printf("%d\n",ans);
}
int main(){
	init();
	work();
	return 0;
}
