// ax + by + c >= 0
void halfPlane(vector<P> &p, db a, db b, db c) {
	vector<P> q;
	rep(i, 0, sz(p)) {
		if(a * p[i].x + b * p[i].y + c >= 0) q.pb(p[i]);
		else {
			int j = (i - 1 + sz(p)) % sz(p);
			if(a * p[j].x + b * p[j].y + c > 0) q.pb(isLL(L(p[i], p[j]), a, b, c));
			j = (i + 1) % sz(p);
			if(a * p[j].x + b * p[j].y + c > 0) q.pb(isLL(L(p[i], p[j]), a, b, c));
		}
	} p = q;
}