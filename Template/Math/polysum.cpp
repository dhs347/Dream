struct polysum {
    static const int D = 101000;
    static const int P = 998244353;
    ll a[D], fac[D], ifac[D], p1[D], p2[D], h[D][2], C[D];
    ll add(ll a, ll b) {a = (a + b) % P; return a < 0 ? a + P : a;}
	ll mul(ll a, ll b) {a = 1ll * a * b % P; return a < 0 ? a + P : a;}
	ll kpow(ll a, ll b) {ll r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
    void init(int M) {
        fac[0] = 1; rep(i, 1, M+5) fac[i] = mul(fac[i-1], i);
        ifac[M+4] = kpow(fac[M+4], P - 2);
        per(i, 0, M+4) ifac[i] = mul(ifac[i+1], i+1);
    }
    ll calcn(int d, ll *a, ll n) { // a[0].. a[d]  a[n]
        if (n <= d) return a[n];
        p1[0] = p2[0] = 1;
        rep(i, 0, d+1) p1[i+1] = mul(p1[i], (n - i) % P);
        rep(i, 0, d+1) p2[i+1] = mul(p2[i], (n - d + i) % P);
        ll ans=0;
        rep(i, 0, d+1) {
        	ll s1 = mul(p1[i], p2[d - i]);
        	ll s2 = mul(ifac[i], ifac[d - i]);
        	ll t = mul(mul(s1, s2), a[i]);
            ans = (d-i)&1 ? add(ans, -t) : add(ans, t);
        }
        return ans;
    }
    ll Polysum(ll n, ll *a, ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]
        a[m+1] = calcn(m, a, m+1);
        rep(i, 1, m+2) a[i] = add(a[i-1], a[i]);
        return calcn(m+1, a, n-1);
    }
    ll qpolysum(ll R, ll n, ll *a, ll m) { // a[0].. a[m] \sum_{i=0}^{n-1} a[i]*R^i
        if (R == 1) return Polysum(n, a, m);
        a[m+1] = calcn(m, a, m+1);
        ll r = kpow(R, P - 2), p3 = 0, p4 = 0, c, ans;
        h[0][0] = 0; h[0][1] = 1;
        rep(i, 1, m+2) {
            h[i][0] = mul(h[i-1][0] + a[i-1], r);
            h[i][1] = mul(h[i-1][1], r);
        }
        rep(i, 0, m+2) {
            ll t = mul(ifac[i], ifac[m+1-i]);
            p3 = i & 1 ? add(p3, -mul(h[i][0], t)) : add(p3, mul(h[i][0], t));
            p4 = i & 1 ? add(p4, -mul(h[i][1], t)) : add(p4, mul(h[i][1], t));
        }
        c = mul(kpow(p4, P - 2), -p3);
        rep(i, 0, m+2) h[i][0] = add(h[i][0], h[i][1] * c);
        rep(i, 0 ,m+2) C[i] = h[i][0];
        ans = add(mul(calcn(m, C, n), kpow(R, n)), -c);
        return ans;
    }
};
