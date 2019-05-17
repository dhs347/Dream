template <class V>
struct BIT{
	V c[N],cc[N],s[N]; int n;
	void Init(int _n,V a[]=NULL) { mem(s,0); mem(c,0); mem(cc,0); n=_n; if (a!=NULL) rep(i,1,n) s[i]=s[i-1]+a[i]; }
	V Q(V a[],int k) { V ans=0; for ( ; k; k-=(k&(-k))) ans+=a[k]; return ans; }
	void U(V a[],int k,V x) {  for ( ; k<=n; k+=(k&(-k))) a[k]+=x;  }
	V Query(int l,int r) { return s[r]-s[l-1]+(r+1)*Q(c,r)-Q(cc,r)-l*Q(c,l-1)+Q(cc,l-1); }
	void Update(int l,int r,V x) { U(c,l,x); U(c,r+1,-x); U(cc,l,l*x); U(cc,r+1,-(r+1)*x); }
}; 

const int M=100005;
template <class V,class E>
struct Tree{
	int n,m,rt,tot,head[N],e[2*M],nxt[2*M],fa[N][22],L[N],R[N],d[N]; E w[2*M]; V v[N],a[N]; BIT<V>T;
	void Init(int _n) { n=_n,tot=m=d[1]=0; mem(head,0); rt=1; }
	void link(int x,int y,E _w=0) { e[++tot]=y,w[tot]=_w,nxt[tot]=head[x],head[x]=tot; }
	int go(int x,int k) { per(i,20,0) if (k>>i&1) x=fa[x][i]; return x; }
	void dfs(int x,int f) {
		L[x]=++m,fa[x][0]=f,d[x]=d[f]+1;
		for (int i=head[x];i;i=nxt[i]) if (e[i]!=f) dfs(e[i],x); R[x]=m;
	}
	void Work() {
		dfs(1,0); rep(i,1,n) a[L[i]]=v[i]; T.Init(n,a);
		rep(j,1,20) rep(i,1,n) fa[i][j]=fa[fa[i][j-1]][j-1];
	}
	int lca(int x,int y) {
		if (d[x]<d[y]) swap(x,y);
		x=go(x,d[x]-d[y]); if (x==y) return x;
		per(i,20,0) if (fa[x][i]!=fa[y][i]) x=fa[x][i],y=fa[y][i];
		return fa[x][0];
	}
	int Query_lca(int x,int y) { return lca(x,y)^lca(x,rt)^lca(y,rt); }
	void Make_root(int x) { rt=x; }
	V Query(int x) {
		if (x==rt) return T.Query(1,n);
		if (lca(x,rt)==x) {
			x=go(rt,d[rt]-d[x]-1);
			return T.Query(1,n)-T.Query(L[x],R[x]);
		}
		return T.Query(L[x],R[x]); 
	}
	void Update(int x,V delta) {
		if (x==rt) { T.Update(1,n,delta); return;  }
		if (lca(x,rt)==x) {
			x=go(rt,d[rt]-d[x]-1);
			T.Update(1,n,delta),T.Update(L[x],R[x],-delta); return;
		}
		T.Update(L[x],R[x],delta); 
	}
}; 
