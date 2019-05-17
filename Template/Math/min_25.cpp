struct Min_25{ 
	// F(i) 要拆成多个完全积性函数的和 
	static const int N = 1e6 + 7;
	int Sqr, m, p[N], id1[N], id2[N], tot, cntp;
	ll g[N], sp[N], h[N], n, w[N];
	bool isp[N];
	// f(p) = p ^ k 
	ll f(int p) { return 1;}
 
	// 要求的积性函数 F(p ^ e) 
	ll F(int p, int e) { return e == 1 ? -1 : 0;}

	// 假设都是质数的完全积性函数前缀和 去掉 f(1) 
	ll calc(ll n) { return n - 1;}

	void prime(int n){
    	cntp = 0;isp[1] = 1;
    	rep(i, 2, n+1) {
        	if(!isp[i]) p[++cntp] = i;
        	for(int j = 1; j <= cntp && i * p[j] <= n; j++){
            	isp[i * p[j]] = 1;
            	if(i % p[j] == 0)break;
        	}
    	}
    	rep(i, 1, cntp+1) sp[i] = sp[i - 1] + f(p[i]);
    	p[++cntp] = INT_MAX;
	}
	
	ll S(ll x, int y){
    	if(x <= 1 || p[y] > x) return 0;
    	int k = (x <= Sqr ? id1[x] : id2[n/x]);
		ll ret = -(g[k] - sp[y-1]);// 质数的答案 
    	for(int i = y; i <= tot && 1ll * p[i] * p[i] <= x; i++){
        	ll t1 = p[i], t2 = 1ll * p[i] * p[i];
        	for(int e = 1; t2 <= x; e++, t1 = t2, t2 *= p[i]) {
    			if (F(p[i], e)) ret += S(x / t1, i + 1) * F(p[i], e);
				ret += F(p[i], e + 1);// 合数的答案 
			}
		}
    	return  ret;
	}
	
	ll solve(ll _n) {
		n = _n;if (n == 0) return 0;
		m = 0;Sqr = sqrt(n);
		tot = upper_bound(p + 1, p + cntp + 1, Sqr) - (p + 1);
		for(ll i = 1, j; i <= n; i = j + 1){
        	j = n / (n / i);
			w[++m] = n / i;
        	g[m] = calc(w[m]);
        	w[m] <= Sqr ? id1[w[m]] = m : id2[j] = m;
    	}
    	rep(j, 1, tot + 1)
        	for(int i = 1; i <= m && 1ll * p[j] * p[j] <= w[i]; i++){
				ll t = w[i] / p[j];
				int k = t <= Sqr ? id1[t] : id2[n / t]; 
        		g[i] -= f(p[j]) * (g[k] - sp[j - 1]);
			}
		return S(n,1) + 1;
	}	
} _U;
