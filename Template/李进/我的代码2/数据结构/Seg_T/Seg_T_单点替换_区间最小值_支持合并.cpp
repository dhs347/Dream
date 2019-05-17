struct Seg_T{
	int rt[N],ls[N<<6],rs[N<<6],v[N<<6],cnt,L,R,pos,x,m;
	void Init(int _m) { v[cnt=0]=oo; m=_m; }
	void push_up(int t) { v[t]=min(v[ls[t]],v[rs[t]]); }
	int new_node(int p=0,int q=0,int x=oo) { ls[++cnt]=p,rs[cnt]=q,v[cnt]=x; return cnt; }
	void U(int &t,int l,int r) {
		if (!t) t=new_node();
		if (l==r) { v[t]=x; return; }
		int mid=(l+r)>>1;
		if (pos<=mid) U(ls[t],l,mid); else U(rs[t],mid+1,r);
		push_up(t); 
	}
	int M(int a,int b){
		if (!a || !b) return a+b;
		int c=new_node(M(ls[a],ls[b]),M(rs[a],rs[b]),min(v[a],v[b]));
		if (ls[c] || rs[c]) push_up(c); return c;
	} 
	int Q(int t,int l,int r) {
		if (L<=l && r<=R) return v[t];
		int mid=(l+r)>>1; int ans=oo;
		if (L<=mid) ans=min(ans,Q(ls[t],l,mid));
		if (R>mid) ans=min(ans,Q(rs[t],mid+1,r));
		return ans;
	}
	void Update(int &t,int _pos,int _x) { pos=_pos,x=_x,U(t,1,m); }
	int Query(int &t,int l,int r) { L=l,R=r; return Q(t,1,m); }
}; 
