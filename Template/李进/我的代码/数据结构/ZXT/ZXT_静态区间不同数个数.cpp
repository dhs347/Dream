struct ZXT{
	int n,m,q,cnt,tot,a[N],T[30*N],s[30*N],c[2][30*N];
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
	int Q(int L,int pos){
		int l=1,r=m,R=0,mid,ret=0;
		while (pos<r) {
			mid=(l+r)>>1;
			if (pos<=mid) Go(L,R,r,mid,0); else
		  	     ret+=s[c[0][L]],Go(L,R,l,mid,1);
		}
		return ret+s[L];
	}
	int query(int L,int R,int l,int r) {
	    return Q(T[L],r)-Q(T[R+1],r)-Q(T[L],l-1)+Q(T[R+1],l-1);
    }
    int Query(int l,int r) { return Q(T[l],r); }
	void Init(int _n,int *_a) {
		n=_n,tot=0; rep(i,1,n) a[i]=_a[i]; int pos[N]; mem(pos,0);
		init_H(); m=n; T[n+1]=build(1,m);
		per(i,n,1) {
		    int &t=pos[H(_a[i])];
		    if (!t) T[i]=update(T[i+1],i,1); else
                T[i]=update(update(T[i+1],t,-1),i,1); t=i;
        }
	}
};
