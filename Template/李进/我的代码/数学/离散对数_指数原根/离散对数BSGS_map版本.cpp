map<ll, int> hash;
ll bsgs(ll a, ll b, ll p) {
	ll xx, yy;
	if (exgcd(a, p, xx, yy) != 1) return -1;
	a %= p;
	ll m = ceil(sqrt(p));
	hash.clear();
	ll tmp, ans = b % p;
	for (int i = 0; i <= m; ++i) {
		hash[ans] = i;
		ans = ans * a % p;
	}
	tmp = qm(a, m, p);
	ans = 1;
	for (int i = 1; i <= m; ++i) {
		ans = ans * tmp % p;
		if (hash[ans] != 0) return i * m - hash[ans];
	}
	return -1;
}
