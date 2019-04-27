vi ans; bool vis[N]; int p[N];
vector<pii> g[N];

void dfs(int u) {
	for( ; p[u] < sz(g[u]); ++p[u]) {
		auto v = g[u][p[u]];
		if(!vis[abs(v.se)]) {
			vis[abs(v.se)] = 1;
			dfs(v.fi);
			ans.pb(-v.se);
		}
	}
}
