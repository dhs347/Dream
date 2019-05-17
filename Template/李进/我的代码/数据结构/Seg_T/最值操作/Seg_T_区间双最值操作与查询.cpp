struct Seg_T{
	#define lc (t<<1)
	#define rc (t<<1|1)
	#define mid ((l+r)>>1)
	int n,L,R,opt; ll x,*a,mx[N<<2],mi[N<<2];
	inline void push_up(int t) { mx[t]=max(mx[lc],mx[rc]); mi[t]=min(mi[lc],mi[rc]); }
	inline void pd(int t,ll d,int opt) {
		if (opt==1) mi[t]=max(mi[t],d),mx[t]=max(mx[t],d);
		if (opt==2) mi[t]=min(mi[t],d),mx[t]=min(mx[t],d);
	}
	inline void push_down(int t){
		if (mi[t]!=0) pd(lc,mi[t],1),pd(rc,mi[t],1),mi[t]=0;
		if (mx[t]!=ooo) pd(lc,mx[t],2),pd(rc,mx[t],2),mx[t]=ooo;
	}
	void update(int t,int l,int r) {
		if (L<=l && r<=R) { pd(t,x,opt); return ; }
		push_down(t);
		if (L<=mid) update(lc,l,mid);
		if (R>mid) update(rc,mid+1,r); push_up(t);
	}
	ll Q_mx(int t,int l,int r){
		if (L<=l && r<=R) return mx[t];
		push_down(t); ll ret=-ooo; 
		if (L<=mid) ret=max(ret,Q_mx(lc,l,mid));
		if (R>mid) ret=max(ret,Q_mx(rc,mid+1,r)); return ret;
	}
	ll Q_mi(int t,int l,int r){
		if (L<=l && r<=R) return mi[t];
		push_down(t); ll ret=ooo; 
		if (L<=mid) ret=min(ret,Q_mi(lc,l,mid));
		if (R>mid) ret=min(ret,Q_mi(rc,mid+1,r)); return ret;
	}
	void B(int t,int l,int r) {
		if (l==r) { mx[t]=mi[t]=a[l]; return; }
		B(lc,l,mid); B(rc,mid+1,r); push_up(t);
	}
	inline void Init(int _n,ll *_a=NULL){ 
		n=_n,a=_a; if (a==NULL) rep(i,1,4*n) mx[i]=ooo,mi[i]=-ooo; else  B(1,1,n); 
	} 
	inline void Update(int l,int r,ll _x,int _opt) { L=l,R=r,x=_x,opt=_opt; update(1,1,n); }//opt==1，max
	inline ll Query(int l,int r,int opt) { L=l,R=r;  return opt ? Q_mx(1,1,n) : Q_mi(1,1,n); }
};
