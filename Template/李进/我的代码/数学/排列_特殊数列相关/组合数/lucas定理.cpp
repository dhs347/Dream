ll Lucas(ll n, ll m,ll base) {
	ll ans = 1;
	while (n && m) {
		ll a = n % base,b = m % base;
		if (a < b) return 0;
		ll ret = fac[b] * fac[a - b] % base;
		ret = fac[a] * Inv(ret, base) % base;
		ans = ans * ret % base;
		n /= base,m /= base;
	}
	return ans;
}

//C(n, m) ≡ C(n/p, m/p) ∗ C(n%p, m%p) % p
