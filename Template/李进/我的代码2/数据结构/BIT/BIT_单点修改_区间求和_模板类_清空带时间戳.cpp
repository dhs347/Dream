template <class V> 
struct BIT{
	V c[N]; int n,t[N],T; inline void Clear() { ++T; }
	inline void Init(int _n) { mem(c,0),mem(t,0),T=0; n=_n; }
	inline V& G(int x) { if (t[x]!=T) c[x]=0,t[x]=T; return c[x]; }
	inline V Q(int k) { V ans=0; for ( ; k; k-=(k&(-k))) ans+=G(k); return ans; }
	inline void U(int k,V x) { for ( ; k<=n; k+=(k&(-k))) G(k)+=x; }
}; 
