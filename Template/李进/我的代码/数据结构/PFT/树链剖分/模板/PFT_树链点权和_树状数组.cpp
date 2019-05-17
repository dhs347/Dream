struct BIT{
    ll c[N],cc[N],s[N]; int n;
    void Init(int _n,ll a[]=NULL) { mem(s,0); mem(c,0); mem(cc,0); n=_n; if (a!=NULL) rep(i,1,n) s[i]=s[i-1]+a[i]; }
    ll Q(ll a[],int k) { ll ans=0; for ( ; k; k-=(k&(-k))) ans+=a[k]; return ans; }
    void U(ll a[],int k,ll x) {  for ( ; k<=n; k+=(k&(-k))) a[k]+=x;  }
    ll Query(int l,int r) { return s[r]-s[l-1]+(r+1)*Q(c,r)-Q(cc,r)-l*Q(c,l-1)+Q(cc,l-1); }
    void Update(int l,int r,ll x) { U(c,l,x); U(c,r+1,-x); U(cc,l,l*x); U(cc,r+1,-(r+1)*x); }
}; 

struct PFT{
    int s[N],top[N],son[N],dep[N],id[N],no[N],f[N];
    int head[N],to[2*N],next[2*N],n,m,cnt;
    ll num[N],a[N]; BIT T;
    void Init(){
        mem(head,-1); mem(son,-1); mem(next,-1); 
        mem(num,0); m=cnt=n=0;
    }
    void addedge(int u,int v) { to[m]=v,next[m]=head[u],head[u]=m++; }
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
    void Build(int _n) {
        n=_n; dfs1(1,0,0); dfs2(1,1);
        rep(i,1,n) a[id[i]]=num[i]; T.Init(n,a);
    }
    void Update(int x,int y,ll v){
        while (top[x]!=top[y]){
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            T.Update(id[top[x]],id[x],v);
            x=f[top[x]];
        }
        if (dep[x]>dep[y]) swap(x,y);
        T.Update(id[x],id[y],v);
    }
    ll Query(int x,int y) {
        ll ret=0;
        while (top[x]!=top[y]) {
            if (dep[top[x]]<dep[top[y]]) swap(x,y);
            ret+=T.Query(id[top[x]],id[x]);
            x=f[top[x]];
        }
        if (dep[x]>dep[y]) swap(x,y);
        return ret+T.Query(id[x],id[y]);
    }
};
