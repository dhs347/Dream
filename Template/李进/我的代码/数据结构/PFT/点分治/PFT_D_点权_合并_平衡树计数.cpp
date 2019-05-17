struct SBT{
	int root,c[N+5][2],s[N+5],cnt,v[N+5];
	void init(){root = cnt = 0;}
	void push_up(int t){ s[t]=s[c[t][0]]+s[c[t][1]]+1; }
	int new_node(int x){ v[++cnt]=x; s[cnt]=1; c[cnt][0]=c[cnt][1]=0; return cnt; }
	void R(int &t,int p){
		int k = c[t][!p];c[t][!p]=c[k][p];c[k][p]=t; 
		s[k]=s[t]; push_up(t); t = k;
	}
	void MT(int &t,int p){
		if (s[c[c[t][p]][p]] > s[c[t][!p]]) R(t,!p); else
		if (s[c[c[t][p]][!p]] > s[c[t][!p]]) R(c[t][p],p),R(t,!p); else return;
		MT(c[t][0],0); MT(c[t][1],1); MT(t,0); MT(t,1);
	}
	void Insert(int &t,int x){
		if (! t){ t = new_node(x); return; }
		s[t]++;
		Insert(c[t][x >= v[t]],x); 
		MT(t,x >= v[t]);
	}
	int Del(int &t,int x){
		int ret;
		s[t]--;
		if (x == v[t] || c[t][x > v[t]] == 0){ 
			ret = v[t];
			if (c[t][0] && c[t][1]) v[t] = Del(c[t][0],x + 1); else t=c[t][0]+c[t][1];
			return ret;
		}
		return Del(c[t][x > v[t]],x);
	}
	int Select(int &t,int k){
		int r=s[c[t][0]]+1;
		return k==r ? v[t] : Select(c[t][k>r],k-r*(k>r));
	}
	int Rank(int &t,int x){
		if (!t) return 1;
		int r=s[c[t][0]]+1;
		return Rank(c[t][x>v[t]],x)+r*(x>v[t]);
	}
};

struct PFT{
    struct node { int y,nxt; } e[N<<1]; SBT T;
    int n,tot,k,rt,head[N],f[N],vis[N],sz[N],v[N]; int s[N],temp[N],flag,_x; ll ans=0;
    void Init(int _n,int _k){ n=_n,tot=0; mem(vis,0),mem(head,0); f[0]=oo; temp[0]=0;  /*  */ k=_k; T.init(); }
    void addedge(int x,int y){ e[++tot].nxt=head[x]; head[x]=tot; e[tot].y=y; }
    void dfs(int x,int fa) {
        if (fa==_x) { rep(i,1,temp[0]) T.Insert(T.root,s[temp[i]]); flag=x; temp[0]=0; }
		//...此处查询 
		int t=k-s[x]+v[_x]+1;
		T.Insert(T.root,t);
		ans+=T.Rank(T.root,t)-1;
		T.Del(T.root,t);
        temp[++temp[0]]=x;
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y] || e[i].y==fa) continue;
            s[e[i].y]=s[x]+v[e[i].y];
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
        s[x]=v; temp[0]=0; T.init(); dfs(flag=_x=x,0);
    }
    void solve(int x,int c) {
        get_rt(x,c,rt=0),x=rt; cal(x,v[x]); vis[x]=1;
        for (int i=head[x]; i; i=e[i].nxt) {
            if (vis[e[i].y]) continue;
            solve(e[i].y,sz[e[i].y]);
        }
    }
    ll Q(){
        //...
        ans=0; solve(1,n);
    }
};
