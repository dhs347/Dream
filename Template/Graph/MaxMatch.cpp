namespace MaxMatch {
	const int N = 1050;
	int link[N], vis[N], use[N], in[N];
	queue<int> Q;
	int dfs(int u, vi g[]) {
		for(auto v : g[u]) {
			if(!vis[v]) {
				vis[v] = 1;
				if(!link[v] || dfs(link[v], g)) { return link[v] = u, 1; }
			}
		}
		return 0;
	}
	int solve(int n, int m, vi g[]) {
		fill_n(link, m+1, 0);
		int ret = 0;
		rep(i, 1, n+1) {
			fill_n(vis, m+1, 0);
			ret += dfs(i, g);
		}
		return ret;
	}
	void MVC(int n, vi g[]) {
		fill_n(vis, n+1, 0);
		per(i, 1, n+1) link[link[i]] = i; 
		rep(i, 1, n+1) if (!link[i]) vis[i] = use[i] = 1, Q.push(i);
		while (!Q.empty()) {
			int u = Q.front(); Q.pop();
			if (use[u] == 1) {
				for (auto v : g[u]) {
					use[v] = 2;
					if (!vis[v]) vis[v] = 1, Q.push(v);
				}
			}else {
				int v = link[u];
				use[v] = 1;
				if (!vis[v]) vis[v] = 1, Q.push(v);
			}
		}
		rep(i, 1, n+1) if (link[i] && !use[link[i]]) use[i] = 2;
		return;
	}
}
