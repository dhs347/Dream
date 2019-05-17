vector<ll> c;
inline bool pan_g(ll g, ll p) {
	for (int i = 0; i < c.size(); ++i)
		if (qm(g, c[i], p) == 1)
			return 0;
	return 1;
}
inline ll findg(ll p) {
	c.clear();
	ll tmp = p ? 1,k = 2;
	while (k * k <= tmp) {
		if (tmp % k == 0) {
			c.push_back(k);
			while (tmp % k == 0) tmp /= k;
		}
		++k;
	}
	if (tmp != 1) c.push_back(tmp);
	for (int i = 0; i < c.size(); ++i)
		c[i] = (p?1) / c[i];
	ll g = 1;
	while (true) {
		if (pan_g(g, p)) return g;
		++g;
	}
	return 0;
}
