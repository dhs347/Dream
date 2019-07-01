struct circle4 {
	static const int N = 1e5 + 7;
	int n, m, u, v, x, y;
	bool vis[N];
	ll f[N][5], du[N], D[N], cnt4[N], cnt3[N], cntl[N], t, ans; // cnt3,4中为包含i号点的三,四元环数量 
	priority_queue<pii> q;
	vi w[N], gg[N], d2, d1;
	set<int> g[N];

	void dfs(int u, int d, int fa) {
		if (d == 2) { d2.pb(u); w[u].pb(fa); return; }
		if (d == 1) d1.pb(u), vis[u] = 1;
		for (auto v : g[u]) if (v != fa) dfs(v, d+1, u);
	}
	
	void solve(int n, vi gg[]) {
		rep(i, 1, n+1) {
			D[i] = du[i] = sz(gg[i]); cnt3[i] = cnt4[i] = 0;
			for (auto v : gg[i]) g[i].insert(v);
		}
		rep(i, 1, n+1) q.push(mp(du[i], i));
		rep(i, 1, n+1) {
			rep(j, 1, 5) f[i][j] = 0; f[i][0] = 1;
		}
		rep(i, 1, 5) rep(j, 1, n+1) for (auto v : gg[j]) f[j][i] += f[v][i-1];
		while (!q.empty()) {
			x = q.top().se; y = q.top().fi; q.pop();
			if (du[x] != y) continue;
			dfs(x, 0, -1);
			for (auto u : d2) {
				ll s = sz(w[u]);
				for (auto v : w[u]) {
					cnt4[v] += s - 1;
					if (vis[u]) cnt3[v]++, t++;
				}	
				cnt4[x] += s * (s - 1) / 2;
				cnt4[u] += s * (s - 1) / 2;
				w[u].clear();
			}
			for(auto u : d1) vis[u] = 0; d1.clear(); d2.clear();
			cnt3[x] += t / 2; t = 0;
			for (auto u : g[x]) {
				q.push(mp(--du[u], u));
				g[u].erase(x);
			}
		}
		//以第一次产生重复位置分类计数 
		rep(i, 1, n+1) { // 计算边数为4的链数 
			ans = f[i][4];
			//第一次重复为第4步
			ans -= cnt4[i] * 2; ll ans3 = f[i][3] - D[i] * D[i] - 2 * cnt3[i]; 
			for (auto v : gg[i]) ans3 -= D[v] - 1; ans -= ans3; // 边数为3的链数 
			for (auto v : gg[i]) ans -= 2 * cnt3[v]; ans += 4 * cnt3[i]; 
			//第一次重复为第3步
			ans -= 2 * cnt3[i] * D[i]; for (auto v : gg[i]) ans -= (D[v] - 1) * D[v]; 
			//第一次重复为第2步 
			ans -= D[i] * f[i][2]; 
			cntl[i] = ans;
		}
	}
} c4;
