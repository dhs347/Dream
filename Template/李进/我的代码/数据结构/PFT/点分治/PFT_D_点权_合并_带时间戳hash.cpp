struct HT{
    int q[1001005],now[1001005]; int *s;
    void init(int *_s){ mem(q,0); mem(now,0); s=_s; }
    void I(int x,int t) { if (now[s[x]]==t) q[s[x]]=min(q[s[x]],x); else q[s[x]]=x,now[s[x]]=t; }
    int Q(int y,int t) { if (now[y]!=t) return -1; else return q[y]; }
};

struct PFT{
    struct node { int y,nxt; } e[N<<1]; HT T;
    int n,tot,k,rt,head[N],f[N],vis[N],sz[N],v[N]; int s[N],temp[N],flag,_x; int ans[2];
    void Init(int _n,int _k){ n=_n,tot=0; mem(vis,0),mem(head,0); f[0]=oo; temp[0]=0;  /*  */ k=_k; T.init(s); }
    void addedge(int x,int y){ e[++tot].nxt=head[x]; head[x]=tot; e[tot].y=y; }
    void dfs(int x,int fa) {
        if (fa==_x) { rep(i,1,temp[0]) T.I(temp[i],_x); flag=x; temp[0]=0; }
		//...此处查询 
        temp[++temp[0]]=x;
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y] || e[i].y==fa) continue;
            s[e[i].y]=(ll)s[x]*v[e[i].y]%_p;
            dfs(e[i].y,x);
        }
    }
    void get_rt(int x,int c,int fa=0) {
        sz[x]=1,f[x]=0;
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y] || e[i].y==fa) continue;
            get_rt(e[i].y,c,x);
            sz[x]+=sz[e[i].y];
            f[x]=max(f[x],sz[e[i].y]);
        }
        f[x]=max(f[x],c-sz[x]);
        if (f[x]<f[rt]) rt=x;
    }
    void cal(int x,int v) {
        //...
        s[x]=v; temp[0]=0; dfs(flag=_x=x,0);
    }
    void solve(int x,int c) {
        get_rt(x,c,rt=0),x=rt; cal(x,v[x]); vis[x]=1;
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y]) continue;
            solve(e[i].y,sz[e[i].y]);
        }
    }
    void Q(){
        //...
        /*答案初值*/ solve(1,n);
    }
};
