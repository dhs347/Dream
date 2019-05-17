struct ST{
	int n,log[20*N],dp[22][20*N]; int *a;
	inline int h(int x,int y) { return a[x]>=a[y] ? x:y; }
	inline void Init(int _n,int *_a){
		n=_n,a=_a,log[0]=-1; rep(i,1,n) log[i]=log[i>>1]+1,dp[0][i]=i;
		rep(i,1,log[n]) rep(j,1,n+1-(1<<i)) dp[i][j]=h(dp[i-1][j],dp[i-1][j+(1<<(i-1))]);
	}
	inline int Q(int l,int r) { int L=log[r-l+1]; return h(dp[L][l],dp[L][r+1-(1<<L)]); }
}; 

int ss[N*20];

struct PFT{
    struct seqtype {
		int x,l,r; int s; seqtype(int _x=0,int _l=0,int _r=0,int _s=0):x(_x),l(_l),r(_r),s(_s) {  } 
	}; seqtype seq[N*20];
	struct qtype {
		int p,l,r,pos; qtype(int _p=0,int _l=0,int _r=0,int _pos=0):p(_p),l(_l),r(_r),pos(_pos){  }
		friend bool operator < (const qtype &a,const qtype &b) { return ss[a.p]+ss[a.pos]<ss[b.p]+ss[b.pos]; }
	};
	struct node { int y,nxt,v; } e[N<<1]; ST T; priority_queue <qtype> P_Q;
    int n,tot,k,rt,head[N],f[N],vis[N],sz[N]; int s[N],flag,_x; int L,R,_R;  ll ans; 
    inline void Init(int _n,int _k){ n=_n,tot=0; mem(vis,0),mem(head,0); f[0]=oo;  /*  */ k=_k; L=1,R=0; }
    inline void addedge(int x,int y,int v){ e[++tot].nxt=head[x]; head[x]=tot; e[tot].y=y; e[tot].v=v; }
    void dfs(int x,int fa) {
        if (fa==_x) { flag=x; _R=R; }
        seq[++R]=seqtype(x,L,_R,s[x]),ss[R]=s[x];
		//...此处查询 
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y] || e[i].y==fa) continue;
            s[e[i].y]=s[x]+e[i].v;
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
    inline void cal(int x,int v) {
        //...
        s[x]=v; L=R+1,_R=R; dfs(flag=_x=x,0);
    }
    void solve(int x,int c) {
        get_rt(x,c,rt=0),x=rt; cal(x,0); vis[x]=1;
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y]) continue;
            solve(e[i].y,sz[e[i].y]);
        }
    }
    inline void Push(int p,int l,int r) { P_Q.push(qtype(p,l,r,T.Q(l,r))); } 
    inline void process(){
    	T.Init(R,ss); qtype g;
    	rep(i,1,R) {
    		if (seq[i].l>seq[i].r) continue;
    		P_Q.push(qtype(i,seq[i].l,seq[i].r,T.Q(seq[i].l,seq[i].r)));
		}
		while (k--) {
			g=P_Q.top(); P_Q.pop(); 
			printf("%d\n",ss[g.p]+ss[g.pos]);
			if (g.l<g.pos) Push(g.p,g.l,g.pos-1);
			if (g.r>g.pos) Push(g.p,g.pos+1,g.r);
		}
	}
    inline void Q(){
        //...
        solve(1,n); process();
    }
};
