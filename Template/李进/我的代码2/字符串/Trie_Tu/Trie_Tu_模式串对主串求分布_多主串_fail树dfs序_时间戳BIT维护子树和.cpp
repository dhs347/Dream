template <class V> 
struct BIT{
	V c[N]; int n,t[N],T; inline void Clear() { ++T; }
	inline void Init(int _n) { mem(c,0),mem(t,0),T=0; n=_n; }
	inline V& G(int x) { if (t[x]!=T) c[x]=0,t[x]=T; return c[x]; }
	inline V Q(int k) { V ans=0; for ( ; k; k-=(k&(-k))) ans+=G(k); return ans; }
	inline void U(int k,V x) { for ( ; k<=n; k+=(k&(-k))) G(k)+=x; }
}; 

struct Tree{
	static const int N=100005,M=100005; int n,m,tot,head[N],e[2*M],nxt[2*M],L[N],R[N]; BIT<ll> T;
	inline void Init(int _n) { n=_n,tot=m=0; mem(head,0); T.Init(n); }
	inline void link(int x,int y) { e[++tot]=y,nxt[tot]=head[x],head[x]=tot; }
	void dfs(int x,int f) { L[x]=++m; for (int i=head[x];i;i=nxt[i]) if (e[i]!=f) dfs(e[i],x); R[x]=m; }
	inline void Update(int x,int k) { T.U(L[x],k); };
	inline ll Query(int x) { return T.Q(R[x])-T.Q(L[x]-1); }
}; 

struct Trie_Tu{
	static const int M=26; int go[N][M],pre[N],toop[N],dep[N],temp[N],str_id[N],cnt,str_cnt,S,t,l,r,f,T; Tree TT;
	inline int h(int c) { return c-'a'; }
	inline int new_node(int d=0) { ++cnt,pre[cnt]=0,mem(go[cnt],0); dep[cnt]=d; return cnt; }
	inline void Init() { str_cnt=cnt=0; S=new_node(); rep(i,0,M-1) go[0][i]=S; } 
    inline void Go(int &p,int c,int f=1) { int &t=go[p][c]; p=t?t:t=new_node(dep[p]+1); if (f) TT.Update(p,1); else /**/; }
    inline int Run(const char s[],int _n=0,int op=0,int f=1) {
        if (!_n) _n=strlen(s); int pos=S,p=op*(_n-1),q=(op?-1:_n); op=1-2*op,T+=f; if (f) TT.T.Clear();
        for (int i=p; i!=q; i+=op) Go(pos,h(s[i]),f); return pos;
    }
    inline void Insert(const char s[],int _n=0,int op=0) { str_cnt++,str_id[str_cnt]=t=Run(s,_n,op,0); /*...*/ }
    inline void Build() {
    	for (toop[l=r=1]=S; l<=r && (f=toop[l++]); )
    		rep(i,0,M-1) if (!go[f][i]) go[f][i]=go[pre[f]][i]; else
    			pre[t=go[f][i]]=go[pre[f]][i], t!=S ? toop[++r]=t : 0;
    	TT.Init(cnt); rep(i,2,cnt) TT.link(pre[i],i); 
		
		TT.dfs(S,0); 
	}
	inline ll Q(int k) { return TT.Query(str_id[k]); }
};
