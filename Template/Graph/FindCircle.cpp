
vector<pair<pii>, int> g[N];
void dfs(int u, int pre) {
	dfn[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		if (g[u][i].se == pre) continue;
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (dfn[v] && dfn[v] <= dfn[u]) {
			k++;
			int p = u; cir[k].pb(p); id[p] = k;
			if (p != v) {do { p = fa[p]; cir[k].pb(p); id[p] = k;
			} while (p != v);}
			if (sz(cir[k]) > 1 && ne[cir[k][0]] != cir[k][1]) reverse(all(cir[k]));
			continue;
		}
		if (!dfn[v]) {fa[v] = u; d[v] = d[u] + w; dfs(v, g[u][i].se);}
	}
}
