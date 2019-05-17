inline ll QM(ll a, ll n, const ll & p) {
	ll ans = 1;
	for (ll tmp = a; n; n >>= 1) {
		if (n & 1) ans = ans * tmp % p;
		tmp = tmp * tmp % p;
	}
	return ans;
}
