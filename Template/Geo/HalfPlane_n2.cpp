// l(a->b ÄæÊ±Õë·½Ïò ) 
void convexCut(vector<P> &p, L l) {
	vector<P> q;
	rep(i, 0, sz(p)) {
		P p1 = p[i], p2 = p[(i + 1) % sz(p)];
		int d1 = sign(det(l.a, l.b, p1));
		int d2 = sign(det(l.a, l.b, p2));
		if(d1 >= 0) q.pb(p1);
		if(d1 * d2 < 0) q.pb(isLL(L(p1, p2), l));
	} p = q;
}
// ax + by + c >= 0
void convexCut(vector<P> &p, db a, db b, db c) {
	vector<P> q;
	rep(i, 0, sz(p)) {
		P p1 = p[i], p2 = p[(i + 1) % sz(p)];
		int d1 = sign(a * p1.x + b * p1.y + c);
		int d2 = sign(a * p2.x + b * p2.y + c);
		if(d1 >= 0) q.pb(p1);
		if(d1 * d2 < 0) q.pb(isLL(L(p1, p2), a, b, c));
	} p = q;
}
