struct SegGraph {
#define ls (rt << 1)
#define rs (ls | 1)
	static const int N = :: N << 3;
	int id[N][2], p[N], tim;
	vector<pii> g[N];
	void init() { rep(i, 0, tim) g[i].clear(); tim = 0; }
	
	void liu(int u, int v, int w) { g[u].pb(mp(v, w)); }
	
	void build(int l, int r, int rt) {
		int *t = id[rt], *fa = id[rt / 2], mid = l + r >> 1;
		t[0] = ++tim, t[1] = ++tim, liu(t[0], t[1], 0);
		if (rt / 2) liu(fa[0], t[0], 0), liu(t[1], fa[1], 0);
		if (l == r) { p[l] = t[0]; return; }
		build(l, mid, ls);
		build(mid+1, r, rs);
	}

	void link(int l, int r, int rt, int L, int R, int w, int o) {
		int *t = id[rt], mid = l + r >> 1;
		if (L <= l && R >= r) {
			if (o) liu(t[o], tim, w);
			else liu(tim, t[o], w);
			return;
		}
		if (L <= mid) link(l, mid, ls, L, R, w, o);
		if (R > mid)  link(mid+1, r, rs, L, R, w, o);
	}

	void link(int l1, int r1, int l2, int r2, int w, int n) { // [l1, r1] -> [l2, r2] weight = w 
		++tim;
		link(1, n, 1, l1, r1, w, 0);
		link(1, n, 1, l2, r2, w, 1);
	}

} G;
