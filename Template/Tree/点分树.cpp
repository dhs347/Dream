// id starts from 1
namespace Centriod {
	const int N = ::N;
	bool vis[N]; int sz[N], par[N]; vi G[N];
	void dfssz(int c,int fa,int Sz,int &rt){
		sz[c] = 1;
		for(auto t : g[c]) if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
		if(!rt && sz[c]*2>Sz) rt=c;
	}
	int dfs(int c){
		int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
		vis[rt] = true;
		for(auto v : g[rt]) if(!vis[v]) {
			int t = dfs(v);
			G[rt].pb(t);
			par[t] = rt;
		}
		return rt;
	}
	void init() { 
		fill_n(G + 1, n, vi()); 
		fill_n(par + 1, n, 0);
	}
};
