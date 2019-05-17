template <class TT>
struct Seg_T{
    #define lson l,mid,rt<<1
    #define rson mid+1,r,rt<<1|1
	int n,L,R; TT s[4*N],lazy[4*N][2],*a,*v;
	inline void push_up(int rt){ s[rt]=s[rt<<1]+s[rt<<1|1]; }
	inline void let(TT *v,TT p,TT q) { v[0]=p,v[1]=q; }
	inline void pd(int rt,int m,TT *v) {
        let(lazy[rt],lazy[rt][0]*v[0],lazy[rt][1]*v[0]+v[1]);
        s[rt]=s[rt]*v[0]+v[1]*m;
	}
	inline void push_down(int rt,int m) {
		if (!lazy[rt][1] && lazy[rt][0]==1) return;
		pd(rt<<1,m-(m>>1),lazy[rt]),pd(rt<<1|1,m>>1,lazy[rt]);
        let(lazy[rt],1,0);
	}
	void B(int l,int r,int rt) {
		let(lazy[rt],1,0);
		if (l==r) { s[rt]=a[l]; return; }
		int mid=(l+r)>>1;
    	B(lson); B(rson); push_up(rt);
	}
	inline void Init(int _n,TT _a[]=NULL){
        n=_n; if (_a==NULL) { mem(s,0); rep(i,0,4*n) let(lazy[i],1,0); return ; }
        a=_a; B(1,n,1);
	}
    void U(int l,int r,int rt){
        if (L<=l && r<=R) { pd(rt,r-l+1,v); return; }
        push_down(rt,r-l+1);
        int mid=(l+r)>>1;
        if (L<=mid) U(lson);
        if (R>mid) U(rson);
        push_up(rt);
    }
    TT Q(int l,int r,int rt) {
        if (L<=l && r<=R) return s[rt];
        push_down(rt,r-l+1);
        int mid=(l+r)>>1; TT ret=0;
        if (L<=mid) ret+=Q(lson);
		if (R>mid) ret+=Q(rson);
        push_up(rt);
        return ret;
    }
    inline void Update(int _L,int _R,TT *_v){ L=_L,R=_R,v=_v; U(1,n,1); }
    inline TT Query(int _L,int _R) { L=_L,R=_R; return Q(1,n,1); }
};
