ll CRT(ll m[],ll a[],ll n) {
	ll M = 1,ans = 0;
	for(ll i=1; i<=n; i++) M *= m[i];
	for(ll i=1; i<=n; i++) {
		ll x, y,Mi = M / m[i];
		exgcd(Mi, m[i], x, y);
		ans = (ans + Mi * x * a[i]) % M;
	}
	if(ans < 0) ans += M;
	return ans;
}

//方程组 X ≡ xi (mod mi) 有整数解。并且在模 M = m1m2...mn 下的解是唯一的，解为x ≡ (x1M1M1 −1 + x2M2M2 −1..xnMnMn −1)(mod M). 其中 Mi = M/mi 而 Mi−1 是 Mi 模 mi 的逆元。
