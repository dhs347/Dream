// O(len^2)
vi BM(vi s) {
	vi C(1, 1), B(1, 1);
	int L = 0, m = 1, b = 1;
	rep(n, 0, sz(s)) {
		ll d = 0;
		rep(i, 0, L+1) (d += 1ll * C[i] * s[n-i]) %= P;
		if(d == 0) ++m;
		else {
			vi T = C;
			ll c = P - d * kpow(b, P - 2) % P;
			while(sz(C) < sz(B) + m) C.pb(0);
			rep(i, 0, sz(B)) C[i + m] = add(C[i + m], mul(c, B[i]));
			if(2 * L <= n) {
				L = n + 1 - L, B = T, b = d, m = 1;
			} else {
				++m;
			}
		}
	}
	reverse(all(C));
	rep(i, 0, sz(C)) C[i] = P - C[i];
	return vi(C.begin(), C.end() - 1);
}
