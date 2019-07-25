#include <bits/stdc++.h>

template <class T>
bool Reduce(T &a,T const &b) {
	return a>b?a=b,1:0;
}

const int XN=1e4+11;
const int INF=2e9;
const long long oo=1e18;

int n;
long long sp[XN];

namespace D {
	struct Edge {
		int to,v;
	};

	std::vector<Edge> G[XN];

	void Run() {
		static bool ud[XN];
		std::priority_queue<std::pair<long long,int>,std::vector<std::pair<long long,int>>,std::greater<std::pair<long long,int>>> Q;
		std::fill(sp+1,sp+1+n,oo);
		std::fill(ud+1,ud+1+n,0);
		sp[1]=0;
		Q.push(std::make_pair(0,1));
		while(!Q.empty()) {
			int pos=Q.top().second;Q.pop();
			if(ud[pos])
				continue;
			ud[pos]=1;
			for(auto &e : G[pos]) {
				int u=e.to;
				if(Reduce(sp[u],sp[pos]+e.v))
					Q.push(std::make_pair(sp[u],u));
			}
		}
	}
}

namespace I {
	struct Edge {
		int to,cap,v;
		Edge *rev,*pre;
	}*G[XN],*preArc[XN];

	void AddEdge(int x,int y,int c) {
		G[x]=new Edge{y,c,0,NULL,G[x]};
		G[y]=new Edge{x,0,0,G[x],G[y]};
		G[x]->rev=G[y];
	}

	int Aug() {
		int d=INF;
		for(int pos=n;preArc[pos];pos=preArc[pos]->rev->to)
			Reduce(d,preArc[pos]->cap-preArc[pos]->v);
		for(int pos=n;preArc[pos];pos=preArc[pos]->rev->to) {
			preArc[pos]->v+=d;
			preArc[pos]->rev->v-=d;
		}
		return d;
	}

	long long Run() {
		static int num[XN],d[XN];
		static Edge *cArc[XN];
		std::fill(num+1,num+n,0);
		std::fill(d+1,d+1+n,0);
		std::copy(G+1,G+1+n,cArc+1);
		num[0]=n;preArc[1]=0;
		long long flow=0;
		for(int pos=1;d[1]<n;) {
			if(pos==n) {
				flow+=Aug();
				pos=1;
			}
			bool adv=0;
			for(Edge *&e=cArc[pos];e;e=e->pre) {
				int u=e->to;
				if(e->cap>e->v && d[u]+1==d[pos]) {
					adv=1;
					preArc[pos=u]=e;
					break;
				}
			}
			if(!adv) {
				if(--num[d[pos]]==0)
					break;
				d[pos]=n;
				for(Edge *e=cArc[pos]=G[pos];e;e=e->pre)
					if(e->cap>e->v)
						Reduce(d[pos],d[e->to]+1);
				num[d[pos]]++;
				if(pos!=1)
					pos=preArc[pos]->rev->to;//cArc
			}
		}
		return flow;
	}
}

int main() {
	//freopen("test1.in","r",stdin);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;std::cin>>T;
	while(T--) {
		int m;std::cin>>n>>m;
		for(int i=1;i<=n;++i) {
			D::G[i].clear();
			I::G[i]=0;
		}
		for(int i=1;i<=m;++i) {
			int x,y,v;
			std::cin>>x>>y>>v;
			D::G[x].push_back({y,v});
		}

		D::Run();

		if(sp[n]==oo)
			std::cout<<0<<'\n';
		else {
			for(int pos=1;pos<=n;++pos)
				for(auto &e : D::G[pos])
					if(sp[e.to]-sp[pos]==e.v)
						I::AddEdge(pos,e.to,e.v);

			std::cout<<I::Run()<<'\n';
		}
	}
	return 0;
}

