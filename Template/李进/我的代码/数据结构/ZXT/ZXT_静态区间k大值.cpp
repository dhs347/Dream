struct ZXT{
	int n,q,cnt,tot,a[N],T[30*N],s[30*N],c[2][30*N],m;
	void init_H() { sort(a+1,a+n+1); cnt=unique(a+1,a+n+1)-a-1; }
	inline int H(int x) { return lower_bound(a+1,a+cnt+1,x)-a; }
	inline void U(int x,int p,int q) { c[0][x]=p,c[1][x]=q; }
	inline void Go(int &x,int &y,int &t,int m,int op) { x=c[op][x],y=c[op][y],t=m+op; }
	int build(int l,int r) {
		int rt=++tot; s[rt]=0; if (l==r) return rt;
		int mid=(l+r)>>1; U(rt,build(l,mid),build(mid+1,r)); return rt;
	}
	int update(int t,int pos,int v){
		int rt=++tot,tmp=rt,l=1,r=m,mid; s[rt]=s[t]+v;
		while (l<r) {
			mid=(l+r)>>1;
			if (pos<=mid) U(rt,++tot,c[1][t]),Go(rt,t,r,mid,0);
					 else U(rt,c[0][t],++tot),Go(rt,t,l,mid,1);
			s[rt]=s[t]+v;
		}
		return tmp;
	}
	int query(int L,int R,int k){
		int l=1,r=m,mid;
		while (l<r) {
			mid=(l+r)>>1;
			if (s[c[0][L]]-s[c[0][R]]>=k) Go(L,R,r,mid,0); else
		  	     k-=s[c[0][L]]-s[c[0][R]],Go(L,R,l,mid,1);
		}
		return l;
	}
	void Init(int _n,int *_a) {
		n=_n,tot=0; rep(i,1,n) a[i]=_a[i]; init_H(); m=cnt; T[n+1]=build(1,m);
		per(i,n,1) T[i]=update(T[i+1],H(_a[i]),1);
	} 
	int Query(int l,int r,int k) { return a[query(T[l],T[r+1],k)]; }
};
