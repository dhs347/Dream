struct Seg_T{
    #define lson l,mid,rt<<1
    #define rson mid+1,r,rt<<1|1
	int n,L,R; ll s[4*N],lazy[4*N],*a,v;
	void push_up(int rt){ s[rt]=max(s[rt<<1],s[rt<<1|1]); }
	void push_down(int rt) {
		if (!lazy[rt]) return;
		s[rt<<1]=lazy[rt<<1]=lazy[rt];
        s[rt<<1|1]=lazy[rt<<1|1]=lazy[rt];
        lazy[rt]=0;
	}
	void B(int l,int r,int rt) {
		lazy[rt]=0;
		if (l==r) { s[rt]=a[l]; return; }
		int mid=(l+r)>>1;
    	B(lson); B(rson); push_up(rt);
	}
	void Init(int _n,ll _a[]=NULL){
        n=_n; if (_a==NULL) { mem(s,0); mem(lazy,0); return ; }
        a=_a; B(1,n,1);
	}
    void U(int l,int r,int rt){
        if (L<=l && r<=R) { lazy[rt]=v; s[rt]=v; return; }
        push_down(rt);
        int mid=(l+r)>>1;
        if (L<=mid) U(lson);
        if (R>mid) U(rson);
        push_up(rt);
    }
    ll Q(int l,int r,int rt) {
        if (L<=l && r<=R) return s[rt];
        push_down(rt);
        int mid=(l+r)>>1; ll ret=0;
        if (L<=mid) ret=max(ret,Q(lson));
		if (R>mid) ret=max(ret,Q(rson));
        push_up(rt);
        return ret;
    }
    void Update(int _L,int _R,ll _v){ L=_L,R=_R,v=_v; U(1,n,1); }
    ll Query(int _L,int _R) { L=_L,R=_R; return Q(1,n,1); }
};
