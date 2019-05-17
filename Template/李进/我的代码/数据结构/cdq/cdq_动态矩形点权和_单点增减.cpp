struct BIT{
	ll c[N]; int n;
	void Init(int _n) { mem(c,0); n=_n; }
	ll Q(int k) { ll ans=0; for ( ; k; k-=(k&(-k))) ans+=c[k]; return ans; }
	void U(int k,ll x) {  for ( ; k<=n; k+=(k&(-k))) c[k]+=x;  }
}; 

struct cdq{
	struct node{ int x,y,op,c,id,h; } q[N],temp[N]; BIT T; int tot,cnt; ll ans[N];
	friend bool operator < (const node &a, const node &b) {//op要满足查询在后
		return a.x<b.x || a.x==b.x && a.y<b.y || a.x==b.x && a.y==b.y && a.op<b.op;  }
	inline void Init(){ tot=cnt=0; mem(ans,0); T.Init(N);}
	inline void I(int x,int y,int op,int c,int h=0){ q[++tot]=node{x,y,op,c,tot,cnt+=h}; }//插入一个点权修改
	inline void Insert(int x1,int y1,int x2,int y2,int op) {//插入一个矩形查询
		I(x2,y2,op,1,1); I(x1-1,y1-1,op,1,0); I(x2,y1-1,op,-1,0); I(x1-1,y2,op,-1,0);
	}
	void solve(int l,int r) {
		if (l==r) return;
		int mid=(l+r)>>1,l1=l,l2=mid+1;
		rep(i,l,r) {
			if (q[i].id<=mid && q[i].op==1) T.U(q[i].y,q[i].c);
			if (q[i].id>mid && q[i].op==2) ans[q[i].h]+=q[i].c*T.Q(q[i].y);
		}
		rep(i,l,r) if (q[i].id<=mid && q[i].op==1) T.U(q[i].y,-q[i].c);
		rep(i,l,r) if (q[i].id<=mid) temp[l1++]=q[i]; else temp[l2++]=q[i];
		rep(i,l,r) q[i]=temp[i]; solve(l,mid); solve(mid+1,r);
	}
	inline void Solve(){
		sort(q+1,q+tot+1); solve(1,tot); rep(i,1,cnt) printf("%lld\n",ans[i]);
	}
};
