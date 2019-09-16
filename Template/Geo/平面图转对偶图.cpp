struct Planar {
	static const int N = 101010, M = 101010;
	// ps id starts from 0
	vector<P> ps;
	// cnte id starts from 0
	int cnte, ne[M];
	bool vis[M];
	// u -> (v, cnte)
	vector<pii> g[N];
	pii E[M];
	vector<db> areas;

	void init() {
		rep(i, 0, sz(ps)) g[i].clear();
		fill_n(vis, cnte, false);
		ps.clear(); cnte = 0;
		areas.clear();
	}
	void adde(int u, int v) {
		g[u].pb(mp(v, cnte));
		E[cnte++] = mp(u, v);
		g[v].pb(mp(u, cnte));
		E[cnte++] = mp(v, u);
	}
	int V;
	bool cmp(const pii &i, const pii &j) {
		P a = ps[i.fi] - ps[V], b = ps[j.fi] - ps[V];
		int o = P(0, 0) < a, t = P(0, 0) < b;
		if(o != t) return o < t;
		return det(a, b) > 0;
	}
	void go(int e) {
		db res = 0;
		while(!vis[e]) {
			res += det(ps[E[e].se], ps[E[e].fi]); vis[e] = 1;
			e = ne[e ^ 1];
		}
		if(res > 0) areas.pb(res / 2);
	}
	void solve(const vector<P> &_ps, const vector<pii> &es) {
		init(); ps = _ps;
		for(auto e : es) adde(e.fi, e.se);
		rep(i, 0, sz(ps)) {
			V = i; sort(all(g[i]), cmp);
			rep(j, 0, sz(g[i])) {
				ne[g[i][j].se] = g[i][(j + 1) % sz(g[i])].se;
			}
		}
		rep(i, 0, cnte) if(!vis[i]) go(i);
	}
};
