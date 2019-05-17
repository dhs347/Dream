typedef pair<ll,ll> pll;
#define x first
#define y second
#define mid ((l+r)>>1)
inline pll operator+(const pll &A,const pll &B){ return pll(max(A.x+B.x,-ooo),max(A.y+B.x,B.y)); }
inline pll max(const pll &A,const pll &B) { return pll(max(A.x,B.x),max(A.y,B.y)); }
struct Seg_T{
	pll now[N<<2],ever[N<<2],v; int L,R,opt,n; ll *a;
	inline void pd(int t,int f) { ever[t]=max(ever[t],now[t]+ever[f]); now[t]=now[t]+now[f]; }
	inline void push_down(int t) { pd(t<<1,t),pd(t<<1|1,t),now[t]=ever[t]=pll(0,0); }
	void B(int t,int l,int r) {
		if (l==r) { ever[t]=now[t]=pll(a[l],-oo); return; }
		now[t]=ever[t]=pll(0,0); B(t<<1,l,mid); B(t<<1|1,mid+1,r);
	}
	void update(int t,int l,int r){
		if (L<=l && r<=R) { now[t]=now[t]+v; ever[t]=max(ever[t],now[t]); return; }
		push_down(t);  if (L<=mid) update(t<<1,l,mid); if (R>mid) update(t<<1|1,mid+1,r);
	}
	ll query(int t,int l,int r) {
		if (l==r) return (opt==1)?max(now[t].x,now[t].y):max(ever[t].x,ever[t].y);
		push_down(t); if (L<=mid) return query(t<<1,l,mid); else query(t<<1|1,mid+1,r);
	}
	inline void Init(int _n,ll *_a) { n=_n,a=_a,B(1,1,n); }
	inline void Update(int l,int r,const pll &_v) { L=l,R=r,v=_v; update(1,1,n); }//v表示元素先+x,再对y取max 
	inline ll Query(int pos,int _opt) { L=pos,opt=_opt; return query(1,1,n); }//单点查询，opt==1为现在的值 
}; 
#undef x 
#undef y
