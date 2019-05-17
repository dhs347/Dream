struct BIT{
	ll c[N],cc[N],s[N]; int n;
	void Init(int _n,ll a[]=NULL) { mem(s,0); mem(c,0); mem(cc,0); n=_n; if (a!=NULL) rep(i,1,n) s[i]=s[i-1]+a[i]; }
	ll Q(ll a[],int k) { ll ans=0; for ( ; k; k-=(k&(-k))) ans+=a[k]; return ans; }
	void U(ll a[],int k,ll x) {  for ( ; k<=n; k+=(k&(-k))) a[k]+=x;  }
	ll Query(int l,int r) { return s[r]-s[l-1]+(r+1)*Q(c,r)-Q(cc,r)-l*Q(c,l-1)+Q(cc,l-1); }
	void Update(int l,int r,ll x) { U(c,l,x); U(c,r+1,-x); U(cc,l,l*x); U(cc,r+1,-(r+1)*x); }
}; 
