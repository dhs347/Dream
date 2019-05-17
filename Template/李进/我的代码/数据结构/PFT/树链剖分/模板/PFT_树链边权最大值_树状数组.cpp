struct BIT{
    ll c[N],a[N],t; int n;
    void Init(int _n,ll x[]=NULL) { 
		mem(c,0); mem(a,0); n=_n; 
		if (x!=NULL) rep(i,1,n) Update(i,x[i]);
	}
    void Update(int k,ll x){
        a[k]=x;
        for ( ; k<=n; k+=(k&(-k))) {
            c[k]=a[k],t=(k&(-k));
            for (int i=1; i<t; i<<=1) c[k]=max(c[k],c[k-i]);
        }
    }
    ll Query(int l,int r) {
        ll ans=0;
        while (r>=l) {
            ans=max(a[r],ans); r--;
            for (; r-(r&(-r))>=l; r-=(r&(-r))) ans=max(ans,c[r]);
        }
        return ans;
    }
};

struct PFT{
	int s[N],top[N],son[N],dep[N],id[N],no[N],f[N];
	int head[N],to[2*N],next[2*N],n,m,cnt;
	ll num[N],a[N],w[2*N]; BIT T;
	void Init(){
		mem(head,-1); mem(son,-1); mem(next,-1);
		mem(num,0); m=cnt=n=0;
	}
	void addedge(int u,int v,ll c) { to[m]=v,w[m]=c,next[m]=head[u],head[u]=m++; }
	void dfs1(int u,int fa,int d){
		dep[u]=d; f[u]=fa; s[u]=1;
		for (int i=head[u]; ~i; i=next[i]) {
			int v=to[i];
			if (v==fa) continue;
			dfs1(v,u,d+1);
			s[u]+=s[v];
			if (son[u]==-1 || s[v]>s[son[u]]) son[u]=v;
		}
	}
	void dfs2(int u,int _top) {
		top[u]=_top; id[u]=++cnt; no[id[u]]=u;
		if (son[u]==-1) return;
		dfs2(son[u],_top);
		for (int i=head[u]; ~i; i=next[i]) {
			int v=to[i];
			if (v!=son[u] && v!=f[u]) dfs2(v,v);
		}
	}
    void edge_init(){
        rep(u,1,n) {
            for (int i=head[u]; ~i; i=next[i]) {
                int v=to[i],t=(dep[u]>dep[v])?u:v;
                if (!num[t]) num[t]=w[i];
            }
        }
    }
	void Build(int _n) {
		n=_n; dfs1(1,0,0); dfs2(1,1); edge_init();
		rep(i,1,n) a[id[i]]=num[i]; T.Init(n,a);
	}
	void Update(int x,int y,ll v){
		while (top[x]!=top[y]){
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			T.Update(id[x],v);
			x=f[top[x]];
		}
		if (x==y) return;
		if (dep[x]>dep[y]) swap(x,y);
		T.Update(id[y],v);
	}
	ll Query(int x,int y) {
		ll ret=0;
		while (top[x]!=top[y]) {
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			ret=max(ret,T.Query(id[top[x]],id[x]));
			x=f[top[x]];
		}
		if (x==y) return ret;
		if (dep[x]>dep[y]) swap(x,y);
		return max(ret,T.Query(id[son[x]],id[y]));
	}
};
