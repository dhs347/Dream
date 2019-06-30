ll kpow(ll x,ll k,ll p) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%p) if (k&1) ret=ret*x%p;
    return ret; 
}

struct Euler{
    vector<ll> P,A; ll phi,g;
    inline bool check_g(ll g, ll p) {
    	rep(i,0,sz(P))
    		if (kpow(g, P[i], p) == 1)
    			return 0;
    	return 1;
    }
    inline void factor(ll m) {
        P.clear(),A.clear();
        for (ll k=2; k*k<=m; ++k) if (m%k==0) {
            int cnt=0;
            while (m%k==0) m/=k,cnt++;
            P.pb(k),A.pb(cnt); 
        }
        if (m>1) P.pb(m),A.pb(1);
    }
    inline bool check(ll m) {
        //if (m==1 || m==2 || m==4) return 1; 
        factor(m);
        if (sz(P)>2 || sz(P)==1 && P[0]==2) return 0;
        if (sz(P)==1) return 1;
        if (P[0]!=2 || P[0]==2 && A[0]>1) return 0;
        return 1;
    }
    inline ll getRoot(ll p) {
        if (p==1 || p==2 || p==4) return phi=p+1>>1,p-1;
        if (!check(p)) return -1;
        phi=p;
    	for (auto t:P) phi=phi/t*(t-1);
    	factor(phi);
    	for (auto &t:P) t=phi/t;
    	for (g=1; __gcd(g,p)!=1 || !check_g(g,p); ++g);
    	return g;
    }
    inline vector<ll> getAllRoot(ll p) {
        vector<ll> ret; ll g=getRoot(p);
        if (g==-1) return ret;
        rep(i,0,phi) if (__gcd((ll)i,phi)==1) ret.pb(kpow(g,i,p));
        sort(all(ret)); return ret;
    }
};
