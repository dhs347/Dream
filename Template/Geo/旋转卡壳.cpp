// 凸包都是顺时针给出
// 【凸包直径】 点-点
T diameter(vector<P> ps) {
	n = sz(ps); T ans = 0;
	if(n <= 1) return 0;
	if(n == 2) return (ps[1] - ps[0]).len();
	rep(i, 0, n) {
		P t = ps[i] - ps[(i + 1) % n];
		while(det(t, ps[(p + 1) % n] - ps[p]) > 0) (++p) %= n;
		ans = max(ans, (ps[i] - ps[p]).len());
		ans = max(ans, (ps[(i + 1) % n] - ps[p]).len());
	}
	return ans;
}
// 【凸包宽度】 点-边
// 【凸包间的最大距离】 点-点
// 【凸包间的最小距离】
T solve(P p[], int n, P q[], int m) {
	int o = 0, t = 0; T ans = inf;
	rep(i, 1, n) if(p[i].y > p[o].y) o = i;
	rep(i, 1, m) if(q[i].y < q[t].y) t = i;
	rep(i, 0, n) {
		P a = p[(o + 1) % n] - p[o]; db tmp;
		while((tmp = det(a, q[(t + 1) % m] - q[t])) < 0) (++t) %= m;
		if(sign(tmp)) ans = min(ans, disToSeg(L(p[o], p[(o + 1) % n]), q[t]));
		else ans = min(ans, disSS(L(p[o], p[(o + 1) % n]), L(q[t], q[(t + 1) % m])));
		(++o) %= n;
	}
	return ans;
}
T work(P p[], int n, P q[], int m) {
	return min(solve(p, n, q, m), solve(q, m, p, n));
}
// 【凸包最小面积外接矩形】
T solve(vector<P> ps) {
	int n = sz(ps); T ans = 1e18;
	int p = 1, l = 1, r;
	rep(i, 0, n) {
		P t = ps[i] - ps[(i + 1) % n];
		while(det(t, ps[(p + 1) % n] - ps[p]) > 0) (++p) %= n;
		while(dot(t, ps[(l + 1) % n] - ps[l]) < 0) (++l) %= n;
		r = (p + 1) % n;
		while(dot(t, ps[(r + 1) % n] - ps[r]) > 0) (++r) %= n;
		ll et = abs(det(ps[p], ps[i], ps[(i + 1) % n]));
		ll ot = abs(dot(t, ps[l] - ps[r]));
		ans = min(ans, (db)et * ot / t.len2());
	}
	return ans;
}
// 【凸包最小周长外接矩形】
