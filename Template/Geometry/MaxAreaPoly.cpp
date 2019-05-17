ld solve_poly(vi &S) {
	assert(sz(S) > 0);
	int sum = 0, hi = S[0];
	vi vals;
	rep(i, 1, sz(S)) {
		int cur = S[i];
		if (cur > hi) swap(cur, hi);
		sum += cur;
		vals.pb(cur);
	}
	if (sum <= hi) return 0;
	auto getAngle = [&](ld D) -> ld{
		ld tot = 0;
		for (int l : vals) tot += 2 * asin(ld(l) / ld(D));
		return tot;
	};
	bool isReflex = (getAngle(hi) < PI);
	auto tooSmall = [&](ld D) {
		ld ang = getAngle(D);
		ld hiAng = 2 * asin(ld(hi) / ld(D));
		if (isReflex) return ang < hiAng;
		else return ang + hiAng >= 2 * PI;
	};
	ld mi = hi, ma = hi + 1;
	int numExpand = 0;
	while (tooSmall(ma)) numExpand++, ma += (ma - mi);
	rep(tim, 0, 50 + numExpand) {
		ld md = mi + (ma - mi) / 2;
		if (tooSmall(md)) mi = md;
		else ma = md;
	}
	ld D = mi, area = 0;
	for (int l : vals) area += ld(l) * sqrt(ld(D) * ld(D) - ld(l) * ld(l)) / 4;
	ld hiArea = ld(hi) * sqrt(ld(D) * ld(D) - ld(hi) * ld(hi)) / 4;
	if (isReflex) area -= hiArea;
	else area += hiArea;
	return area;
}
