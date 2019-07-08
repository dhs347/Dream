namespace ET {
	const int N = ::N << 1;
	Gra g, T; int L, n, sz[N];
	void dfssz(int u, int fa, int Sz, int &rt) {
		sz[u] = 1;
		for(int i = g.hd[u]; ~i; i = g.ne[i]) if(!vis[i] && g.to[i] != fa) {
			int v = g.to[i];
			dfssz(v, u, Sz, rt);
			if(rt == -1 || max(sz[g.to[rt]], Sz - sz[g.to[rt]]) > max(sz[v], Sz - sz[v])) rt = i;
		}
	}
	int dfs(int u) {
		int I = 0; dfs(u, 0, 0, I);
		if(sz[u] == n) T.init(n);
		if(sz[u] == 1) return u;
		dfs(u, 0, sz[u], I = -1);
		vis[I] = vis[I ^ 1] = true;
		int _ = (I >> 1) + 1 + n, st = g.fr[I >> 1 << 1], ed = g.to[I >> 1 << 1];
		T.add(_, build(st));
		T.add(_, build(ed));
		return _;
	}
	void rebuild(int u, int fa, const Gra &G) {
		if(u == 1) L = n = ::n, g.init(n << 1);
		bool F = 0; int pre = u;
		for(int i = G.hd[u]; ~i; i = G.ne[i]) if(G.to[i] != fa) {
			if(F) {
				g.add(pre, ++n, 0);
				g.add(n, G.to[i], G.val[i]);
				pre = n;
			} else {
				g.add(u, G.to[i], G.val[i]);
				F = 1;
			}
			rebuild(G.to[i], u, G);
		}
	}
}
