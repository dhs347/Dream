struct Seg_T{
    #define lson l,mid,rt<<1
    #define rson mid+1,r,rt<<1|1
    int n,L,R; ll s[4*N],*a,v,mx[4*N],mc[4*N],se[4*N];
    inline void push_up(int rt){
    	int lc=rt<<1,rc=rt<<1|1;
    	s[rt]=s[lc]+s[rc];
    	mx[rt]=max(mx[lc],mx[rc]);
    	se[rt]=max(se[lc],se[rc]); mc[rt]=0;
    	if (mx[lc]!=mx[rc]) se[rt]=max(se[rt],min(mx[lc],mx[rc]));
    	if (mx[rt]==mx[lc]) mc[rt]+=mc[lc];
    	if (mx[rt]==mx[rc]) mc[rt]+=mc[rc];
	}
	inline void pd(int rt,ll v) {
		if (v>=mx[rt]) return;
		s[rt]+=mc[rt]*(v-mx[rt]); mx[rt]=v;
	}
    inline void push_down(int rt) { pd(rt<<1,mx[rt]); pd(rt<<1|1,mx[rt]); }
    void B(int l,int r,int rt) {
        if (l==r) { s[rt]=mx[rt]=a[l]; mc[rt]=1; se[rt]=-oo; return; }
        int mid=(l+r)>>1;
        B(lson); B(rson); push_up(rt);
    }
    void Init(int _n,ll _a[]=NULL){
        n=_n; if (_a==NULL) { mem(s,0); mem(mx,-1); mem(se,-1); return ; }
        a=_a; B(1,n,1);
    }
    void U(int l,int r,int rt){
    	if (v>=mx[rt]) return ;
        if (v>se[rt] && L<=l && r<=R) { pd(rt,v); return; }
        push_down(rt);
        int mid=(l+r)>>1;
        if (L<=mid) U(lson);
        if (R>mid) U(rson);
        push_up(rt);
    }
    ll Q_max(int l,int r,int rt) {
        if (L<=l && r<=R) return mx[rt];
        push_down(rt);
        int mid=(l+r)>>1; ll ret=-oo;
        if (L<=mid) ret=max(ret,Q_max(lson));
        if (R>mid) ret=max(ret,Q_max(rson));
        /*push_up(rt);*/ return ret;
    }
    ll Q_sum(int l,int r,int rt) {
        if (L<=l && r<=R) return s[rt];
        push_down(rt);
        int mid=(l+r)>>1; ll ret=0;
        if (L<=mid) ret+=Q_sum(lson);
        if (R>mid) ret+=Q_sum(rson);
        /*push_up(rt);*/ return ret;
    }
    void Update(int _L,int _R,ll _v){ L=_L,R=_R,v=_v; U(1,n,1); }
    ll Query(int _L,int _R,int op) { L=_L,R=_R; return op ? Q_max(1,n,1) : Q_sum(1,n,1); }
};
