template <class V>
struct Seg_T{
	int rt[N],ls[N<<6],rs[N<<6],cnt,L,R,pos,m; V v[N<<6],x;
	void Init(int _m) { v[cnt=0]=0; mem(rt,0); m=_m; }
	void push_up(int t) { v[t]=v[ls[t]]+v[rs[t]]; }
	int new_node(int p=0,int q=0,V x=0) { ls[++cnt]=p,rs[cnt]=q,v[cnt]=x; return cnt; }
	void U(int &t,int l,int r) {
		if (!t) t=new_node();
		if (l==r) { v[t]=x; return; }
		int mid=(l+r)>>1;
		if (pos<=mid) U(ls[t],l,mid); else U(rs[t],mid+1,r);
		push_up(t); 
	}
	int M(int a,int b,int l){
		if (!a || !b) return a+b;
		int c=new_node(M(ls[a],ls[b],l-(l>>1)),M(rs[a],rs[b],l>>1),v[a]+v[b]);
		if (l==1) v[c]=max(v[a],v[b]);
		if (ls[c] || rs[c]) push_up(c); return c;
	} 
	V Q(int t,int l,int r) {
		if (!t) return 0;
		if (L<=l && r<=R) return v[t];
		int mid=(l+r)>>1; V ans=0;
		if (L<=mid) ans+=Q(ls[t],l,mid);
		if (R>mid) ans+=Q(rs[t],mid+1,r);
		return ans;
	}
	void Update(int &t,int _pos,V _x) { pos=_pos,x=_x,U(t,1,m); }
	int Query(int &t,int l,int r) { L=l,R=r; return Q(t,1,m); }
}; 

//混合规则：单点叶子合并为max，非叶子合并为和；并且注意空间分配，有时候大了小了均会超时； 数值（下标）在小范围内可以代替map合并
//线段树T(A)维护数组A[]区间和(单点替换),C=max(A,B),合并构造T(C)=M(T(A),T(B))，所以要传入管辖区间长度，特判单叶子节点