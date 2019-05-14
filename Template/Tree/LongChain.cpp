struct LongChain{
	static const int N = ::N;
	int wson[N] , top[N] , dep[N] , lg[N];
	int jump[N][20] , id[N] , who[N] , rwho[N] , _;
	void dfs(int c,int fa,vi g[]){
		dep[c]=1;int &s=wson[c]=top[c]=0;
		jump[c][0]=fa;rep(i,1,20) jump[c][i]=jump[jump[c][i-1]][i-1];
		for(auto t:g[c]) if(t!=fa)
			dfs(t,c,g),dep[c]=max(dep[t]+1,dep[c]),(dep[t]>=dep[s])&&(s=t);
	}
	void dfs2(int c,int fa,int rc,vi g[]){
		if(!top[c]) top[c]=c,rc=c;
		who[id[c]=++_]=c;rwho[_]=rc;
		int s=wson[c];
		if(s) top[s]=top[c],dfs2(s,c,jump[rc][0],g);
		for(auto t:g[c]) if(t!=fa&&t!=s) dfs2(t,c,t,g);
	}
	void Build(vi g[]){
		dfs(1,0,g);_=0;dfs2(1,0,1,g);
		rep(i,2,N) lg[i]=lg[i>>1]+1;
	}
	void solve(int c, int fa, vi g[]) {
		for(auto t : g[c]) if(t != fa) solve(t, c, g);
		if(wson[c]) {
			// upd c by wson[c], O(1) or O(log(n))
		} else {
			// c is leaf
		}
		for(auto t : g[c]) if(t != fa && t != wson[c]) {
			// brute force upd c by t
		}
		// 注意统计以 c 为起点的链的答案，注意深度的限制（两棵子树都要注意） 
	}
	// kth_par should exist
	int kth_par(int x,int k){
		if(k==0) return x;
		int j0=1<<lg[k];
		int p0=jump[x][lg[k]];
		int j1=k-j0;
		int del=id[p0]-id[top[p0]];
		if(del>=j1) return who[id[p0]-j1];
		else return rwho[id[top[p0]]+j1-del];
	}
}hc;
