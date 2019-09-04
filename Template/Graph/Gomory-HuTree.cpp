Dinic<int> G;

struct GHT{
	static const int N = 1e5 + 100, M = 17; // (1 << M) > n
	int id[N], tmp[N], n, f[N][M], h[N][M], dep[N];
	vector<pii> g[N];
	void ini(int _n) { n = _n; G.ini(n + 5); rep(i, 1, n+1) id[i] = i, g[i].clear(); }
	void link(int u, int v, int w) { G.link(u, v, w); G.link(v, u, w);}
	void solve(int l, int r) {
		if (l == r) return;
		int s = id[l], t = id[l+1];
		for(int i = 0; i < G.e; i += 2) G.cap[i] += G.cap[i+1], G.cap[i+1] = 0; 
		int w = G.run(s, t); 
		g[s].pb(mp(t, w));
		g[t].pb(mp(s, w));
		int cl = l, cr = 0;
		rep(i, l, r+1) {
			if (G.lv[id[i]] != -1) id[cl++] = id[i];
			else tmp[cr++] = id[i];
		}
		rep(i, 0, cr) id[cl + i] = tmp[i];
		solve(l, cl - 1);
		solve(cl, r);
	}
	
	void dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		for (auto v : g[u]) if (v.fi != fa) {
			f[v.fi][0] = u; h[v.fi][0] = v.se;
			rep(i, 1, M) {
				f[v.fi][i] = f[f[v.fi][i-1]][i-1];
				h[v.fi][i] = min(h[v.fi][i-1], h[f[v.fi][i-1]][i-1]);
			} 
			dfs(v.fi, u);
		}
	}
	
	void build() { solve(1, n); dfs(1, 0); }
	
	int get(int u, int v) { // ×¢Òâ long long 
		int res = pw(30);
		if (dep[u] < dep[v]) swap(u, v);
		per(i, 0, M) if (dep[f[u][i]] >= dep[v]) res = min(res, h[u][i]), u = f[u][i]; 
		per(i, 0, M) if (f[u][i] != f[v][i]) res = min(res, min(h[u][i], h[v][i])), u = f[u][i], v = f[v][i];
		if (u != v) res = min(res, min(h[u][0], h[v][0]));
		return res;
	}
	
} tr;
