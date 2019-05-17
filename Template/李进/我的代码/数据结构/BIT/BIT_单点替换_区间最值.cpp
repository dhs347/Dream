struct BIT{
    ll c[N],a[N],t; int n;
    void Init(int _n,ll x[]=NULL) { 
		mem(c,0); mem(a,0); n=_n; 
		if (x!=NULL) rep(i,1,n) Update(i,x[i]);
	}
    void Update(int k,ll x){
        a[k]=x;
        for ( ; k<=n; k+=(k&(-k))) {
            c[k]=a[k],t=(k&(-k));
            for (int i=1; i<t; i<<=1) c[k]=max(c[k],c[k-i]);
        }
    }
    ll Query(int l,int r) {
        ll ans=0;
        while (r>=l) {
            ans=max(a[r],ans); r--;
            for (; r-(r&(-r))>=l; r-=(r&(-r))) ans=max(ans,c[r]);
        }
        return ans;
    }
};
