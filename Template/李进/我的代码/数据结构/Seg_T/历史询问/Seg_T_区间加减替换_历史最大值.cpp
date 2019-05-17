struct Seg_T{
	int n,L,R,opt; ll *a,mx[N<<2],add[N<<2],cover[N<<2],_mx[N<<2],_add[N<<2],_cover[N<<2],x;
	inline void push_up(int t) {
		mx[t]=max(mx[t<<1],mx[t<<1|1]);
		_mx[t]=max(_mx[t<<1],_mx[t<<1|1]);
	}
	inline void pd(int t,int f){
		_mx[t]=max(_mx[t],max(_cover[f],mx[t]+_add[f]));
		if (cover[t]==-oo) _add[t]=max(_add[t],add[t]+_add[f]);
		else _cover[t]=max(_cover[t],cover[t]+_add[f]);
		if (add[f]) {
			if (cover[t]!=-oo) cover[t]+=add[f]; else add[t]+=add[f];
			mx[t]+=add[f];
		}
		if (cover[f]!=-oo) mx[t]=cover[t]=cover[f],add[t]=0;
		_cover[t]=max(_cover[t],max(cover[t],_cover[f]));
		_add[t]=max(_add[t],add[t]);
	}
	inline void push_down(int t) {
		pd(t<<1,t),pd(t<<1|1,t);
		add[t]=_add[t]=0; cover[t]=_cover[t]=-oo;
	}
	void B(int t,int l,int r) {
		add[t]=_add[t]=0,cover[t]=_cover[t]=-oo;
		if (l==r) { mx[t]=_mx[t]=a[l]; return; }
		int mid=(l+r)>>1; B(t<<1,l,mid); B(t<<1|1,mid+1,r); push_up(t);
	}
	void update(int t,int l,int r){
		if (l!=r) push_down(t); int mid=(l+r)>>1;
		if (L<=l && r<=R) {
			if (opt==0) mx[t]+=x,add[t]+=x,_add[t]+=x;
			if (opt==1) cover[t]=_cover[t]=mx[t]=x;
			_mx[t]=max(_mx[t],mx[t]); return ;
		}
		if (L<=mid) update(t<<1,l,mid);
		if (R>mid) update(t<<1|1,mid+1,r); push_up(t);
	}
	ll query(int t,int l,int r) {
		if (l!=r) push_down(t);
		int mid=(l+r)>>1; ll ans=-oo;
		if (L<=l && r<=R) return (opt?_mx[t]:mx[t]);
		if (L<=mid) ans=max(ans,query(t<<1,l,mid));
		if (R>mid) ans=max(ans,query(t<<1|1,mid+1,r)); return ans;
	}
	inline void Update(int l,int r,ll _x,int _opt) { L=l,R=r,x=_x,opt=_opt; update(1,1,n); }
	inline ll Query(int l,int r,int _opt) { L=l,R=r,opt=_opt; return query(1,1,n); }
	inline void Init(int _n,ll *_a) { n=_n,a=_a; B(1,1,n); }
}; 
