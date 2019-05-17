ll efunc(ll p) {
	ll ans = p, m = p;
	for (ll k=2; k*k<=m; k++) {
		if (m % k == 0) {
			ans /= k;
			ans *= (k-1);
			while (m % k == 0) m /= k;
		}
	}
	ans /= m;
	ans *= max(m-1,0);
}
