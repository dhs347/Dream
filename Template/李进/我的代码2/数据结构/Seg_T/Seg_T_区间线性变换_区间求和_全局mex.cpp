struct Seg_T{
    #define lson l,mid,rt<<1
    #define rson mid+1,r,rt<<1|1
	int n,L,R; ll s[4*N],tag[4*N][2],*a,*v;
	void pd(int rt,int m,ll* v) {
		s[rt]=s[rt]*v[1]+m*v[0];
		tag[rt][1]*=v[1],tag[rt][0]=tag[rt][0]*v[1]+v[0];
	}
	void push_up(int rt){ s[rt]=s[rt<<1]+s[rt<<1|1]; }
	void push_down(int rt,int m) {
		if (!tag[rt][0] && tag[rt][1]==1) return;
        pd(rt<<1,m-(m>>1),tag[rt]);
        pd(rt<<1|1,m>>1,tag[rt]);
        tag[rt][0]=0,tag[rt][1]=1;
	}
	void B(int l,int r,int rt) {
		tag[rt][0]=0,tag[rt][1]=1;
		if (l==r) { s[rt]=a[l]; return; }
		int mid=(l+r)>>1;
    	B(lson); B(rson); push_up(rt);
	}
	void Init(int _n,ll _a[]=NULL){
        n=_n; if (_a==NULL) { mem(s,0); rep(i,0,n) tag[i][0]=0,tag[i][1]=1; return; }
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
    ll Q(int l,int r,int rt) {
        if (L<=l && r<=R) return s[rt];
        push_down(rt,r-l+1);
        int mid=(l+r)>>1; ll ret=0;
        if (L<=mid) ret+=Q(lson);
		if (R>mid) ret+=Q(rson);
        push_up(rt);
        return ret;
    }
    void Update(int _L,int _R,ll* _v){ L=_L,R=_R,v=_v; U(1,n,1); }
    ll Query(int _L,int _R) { L=_L,R=_R; return Q(1,n,1); }
    int QQ(int l,int r,int rt) {
    	if (l==r) return l;
    	push_down(rt,r-l+1); int mid=(l+r)>>1;
    	return (s[rt<<1]<mid-l+1) ? QQ(l,mid,rt<<1) : QQ(mid+1,r,rt<<1|1);
	}
    int Query_mex() { return QQ(1,n,1); }
};
