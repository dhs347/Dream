struct ZXT{
	int n,M,rt[N],ls[N*60],rs[N*60],s[N*60],L,R,d;
	inline void Init(int _M) { n=0,M=_M; }
	inline int new_node(int _l,int _r,int _s) { s[++n]=_s,ls[n]=_l,rs[n]=_r; return n; }
	void U(int &x,int y,int l,int r) {
		x=new_node(ls[y],rs[y],s[y]+d);
		if (l==r) return; int mid=l+r>>1;
		if (L<=mid) U(ls[x],ls[y],l,mid); else U(rs[x],rs[y],mid+1,r);
	}
	int Q(int x,int l,int r) {
		if (!x) return 0;
		if (L<=l && r<=R) return s[x];
		int mid=l+r>>1,sum=0;
		if (L<=mid) sum+=Q(ls[x],l,mid);
		if (R>mid) sum+=Q(rs[x],mid+1,r);
		return sum;
	}
	inline void Update(int x,int _L,int _d) { L=_L,d=_d; U(rt[x],rt[x],0,M); }
	inline int Query(int x,int _L,int _R) { L=_L,R=_R; return Q(rt[x],0,M); }
	inline void Copy(int x,int y) { rt[x]=rt[y]; }
}; 
