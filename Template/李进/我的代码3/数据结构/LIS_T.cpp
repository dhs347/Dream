struct LIS_T{
	int n,*a,dep[N],f[N],c[N],cnt,t; vi V[N];
	inline void Clear() { rep(i,0,n+1) dep[i]=0,f[i]=-1,c[i]=0,V[i].clear(); cnt=0; }
	inline void I(int x) {
		t=dep[x]=lower_bound(c+1,c+cnt+1,x)-c;
		c[t]=x,V[t].pb(x),f[x]=c[t-1],cnt+=(t>cnt);
	} 
	inline void Build() { rep(i,1,n+1) I(a[i]); }
	inline void Init(int _a[],int _n) { a=_a,n=_n; Clear(); Build(); }
};

/*
*
* 注： LIS 树模板
*
* 用户可以调用接口 Init(a,n)+Build()
*
* 详细说明请看 md 文件
*
*/