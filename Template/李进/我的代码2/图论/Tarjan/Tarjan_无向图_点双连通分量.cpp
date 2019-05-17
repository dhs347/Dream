const int _N=1e6+5,_M=1e6+5;
struct Tu{
	int head[_N],nxt[_M],e[_M],n,tot; ll v[_N],w[_M];
	void Init(int _n) { n=_n,mem(head,0),tot=0; }
	void I(int x,int y,ll _w) { e[++tot]=y,w[tot]=_w; nxt[tot]=head[x],head[x]=tot; }
};

struct Tarjan {
	int n,top,top2,cnt,dfn[_N],low[_N],s[_N],s2[_N],id[_M],t; 
	vi cut,D[_N],E[_N],no[_N]; bool mark[_M];
	void dfs(Tu &A,int u,int d,int p) {
		int sec=0,son=d>1;
		dfn[u]=low[u]=d,s[++top]=u;
		for (int i=A.head[u],v; i; i=A.nxt[i]) {
			if (!mark[i+1>>1]) mark[s2[++top2]=i+1>>1]=1;
			if (!dfn[v=A.e[i]]) {
				dfs(A,v,d+1,u),low[u]=min(low[u],low[v]);
				if(low[v]>=dfn[u]) {
					if (++son==2) cut.pb(u);
					D[++cnt].clear(),D[cnt].pb(u),no[u].pb(cnt),E[cnt].clear();
					do E[cnt].pb(s2[top2]),id[s2[top2]]=cnt; while (s2[top2--]!=i+1>>1);
					do D[cnt].pb(s[top]),no[s[top]].pb(cnt); while (s[top--]!=v);
				}
			} else if(v!=p || sec++) low[u]=min(low[u],dfn[v]);
		}
	}
	void solve(Tu &A,Tu &B) {
	    n=A.n,top=top2=-1,cnt=t=0,mem(dfn,0),mem(low,0),mem(mark,0),cut.clear();
		rep(i,1,n) if(!dfn[i]) dfs(A,i,1,0);
		B.Init(cnt+cut.size()),mem(B.v,0);
		rep(k,1,cnt) for (auto i:E[k]) B.v[k]+=A.w[i];
		rep(i,1,n) if (no[i].size()>1) {
			++t,B.v[cnt+t]=A.v[i];
			for (auto k:no[i]) B.I(k,k+t,0),B.I(k+t,k,0);
		}
    }
	void print() {
		debug(cnt);
		rep(i,1,cnt) {
			debug(i);
			debug(D[i].size());
			debug_set(D[i]);
			debug(E[i].size());
			debug_set(E[i]);
		}
		debug(cut.size());
		debug_set(cut);
	}
};
