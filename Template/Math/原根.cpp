ll Pow(ll x,ll k,ll p) {
    ll ret=1;
    for (; k; k>>=1,x=x*x%p) if (k&1) ret=ret*x%p;
    return ret; 
}

struct Euler{
    vector<ll> c;
    inline bool check_g(ll g, ll p) {
    	rep(i,0,sz(c))
    		if (Pow(g, c[i], p) == 1)
    			return 0;
    	return 1;
    }
    inline ll getRoot(ll p) {
    	c.clear();
    	ll tmp=p-1,g;
    	for (ll k=2; k*k<=tmp; ++k)
    		if (tmp % k == 0) {
    			c.pb(k);
    			while (tmp % k == 0) tmp /= k;
    		}
    	if (tmp != 1) c.pb(tmp);
    	rep(i,0,sz(c)) c[i] = (p-1) / c[i];
    	for (g=1; !check_g(g,p); ++g);
    	return g;
    }
};
