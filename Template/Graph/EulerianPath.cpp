vi ans;
bool vis[N];
vector<pii> g[N];

void dfs(int u) {
	for(auto v : g[u]) if(!vis[abs(v.se)]) {
		vis[abs(v.se)] = 1;
		dfs(v.fi);
		ans.pb(-v.se);
	}
}
