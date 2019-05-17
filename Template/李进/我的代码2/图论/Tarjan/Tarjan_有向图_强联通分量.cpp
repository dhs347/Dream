const int _N=1e6+5,_M=1e6+5;
struct Tu{
	int head[_N],nxt[_M],e[_M],n,tot; ll v[_N],w[_M];
	void Init(int _n) { n=_n,mem(head,0),tot=0; }
	void I(int x,int y,ll _w) { e[++tot]=y,w[tot]=_w; nxt[tot]=head[x],head[x]=tot; }
};

struct Tarjan{
	int id[_N],dfn[_N],low[_N],s[_N],n,r,t,tot; bool in[_N];
	void dfs(Tu &A,int x) {
		dfn[x]=low[x]=++t,in[x]=1,s[++r]=x;
		for (int i=A.head[x],y; i; i=A.nxt[i])
			if (!dfn[y=A.e[i]]) dfs(A,y),low[x]=min(low[x],low[y]); else 
			if (in[y]) low[x]=min(low[x],dfn[y]);
		if (low[x]==dfn[x]) { ++tot; while (r && s[r+1]!=x) id[s[r]]=tot,in[s[r--]]=0; }
	}
	void solve(Tu &A,Tu &B) {
		n=A.n; mem(dfn,0); mem(low,0); mem(in,0); r=tot=t=0;
		rep(x,1,n) if (!dfn[x]) dfs(A,x); B.Init(tot); mem(B.v,0); 
		rep(x,1,n) for (int i=A.head[x]; i; i=A.nxt[i]) 
			if (id[x]==id[A.e[i]]) B.v[id[x]]+=A.w[i]; else B.I(id[x],id[A.e[i]],A.w[i]);
		//rep(x,1,n) B.v[id[x]]+=A.v[x];
	}
};
