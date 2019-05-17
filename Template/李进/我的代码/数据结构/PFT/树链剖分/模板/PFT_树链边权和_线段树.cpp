struct Seg_T{
    #define lson l,mid,rt<<1
    #define rson mid+1,r,rt<<1|1
	int n,L,R; ll s[4*N],lazy[4*N],*a,v;
	void push_up(int rt){ s[rt]=s[rt<<1]+s[rt<<1|1]; }
	void push_down(int rt,int m) {
		if (!lazy[rt]) return;
		lazy[rt<<1]+=lazy[rt];
        lazy[rt<<1|1]+=lazy[rt];
        s[rt<<1]+=(m-(m>>1))*lazy[rt];
        s[rt<<1|1]+=(m>>1)*lazy[rt];
        lazy[rt]=0;
	}
	void B(int l,int r,int rt) {
		lazy[rt]=0;
		if (l==r) { s[rt]=a[l]; return; }
		int mid=(l+r)>>1;
    	B(lson); B(rson); push_up(rt);
	}
	void Init(int _n,ll _a[]=NULL){
        n=_n; if (_a==NULL) { mem(s,0); mem(lazy,0); return ; }
        a=_a; B(1,n,1);
	}
    void U(int l,int r,int rt){
        if (L<=l && r<=R) { lazy[rt]+=v; s[rt]+=v*(r-l+1); return; }
        push_down(rt,r-l+1);
        int mid=(l+r)>>1;
        if (L<=mid) U(lson);
        if (R>mid) U(rson);
        push_up(rt);
    }
    ll Q(int l,int r,int rt) {
        if (L<=l && r<=R) return s[rt];
        push_down(rt,r-l+1);
        int mid=(l+r)>>1; ll ret=0;
        if (L<=mid) ret+=Q(lson);
		if (R>mid) ret+=Q(rson);
        push_up(rt);
        return ret;
    }
    void Update(int _L,int _R,ll _v){ L=_L,R=_R,v=_v; U(1,n,1); }
    ll Query(int _L,int _R) { L=_L,R=_R; return Q(1,n,1); }
};

struct PFT{
	int s[N],top[N],son[N],dep[N],id[N],no[N],f[N];
	int head[N],to[2*N],next[2*N],n,m,cnt;
	ll num[N],a[N],w[2*N]; Seg_T T;
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
			T.Update(id[top[x]],id[x],v);
			x=f[top[x]];
		}
		if (x==y) return;
		if (dep[x]>dep[y]) swap(x,y);
		T.Update(id[son[x]],id[y],v);
	}
	ll Query(int x,int y) {
		ll ret=0;
		while (top[x]!=top[y]) {
			if (dep[top[x]]<dep[top[y]]) swap(x,y);
			ret+=T.Query(id[top[x]],id[x]);
			x=f[top[x]];
		}
		if (x==y) return ret;
		if (dep[x]>dep[y]) swap(x,y);
		return ret+T.Query(id[son[x]],id[y]);
	}
};