struct BIT{
	ll c[N]; int n;
	void Init(int _n) { mem(c,0); n=_n; }
	ll Q(int k) { ll ans=0; for ( ; k; k-=(k&(-k))) ans+=c[k]; return ans; }
	void U(int k,ll x) {  for ( ; k<=n; k+=(k&(-k))) c[k]+=x;  }
}; 
