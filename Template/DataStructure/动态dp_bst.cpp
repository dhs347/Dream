int n, m, a[N], sz[N], wson[N], f[N][2], h[N][2];
int to[N << 1], ne[N << 1], hd[N], _;
inline void ae(int u, int v) { to[++_] = v, ne[_] = hd[u], hd[u] = _; }
void dfs(int u, int fa) {
	sz[u] = 1;
	for(int i = hd[u]; i; i = ne[i]) if(to[i] != fa) {
		int v = to[i];
		dfs(v, u);
		// upd f[u]
		sz[u] += sz[v];
		(sz[v] > sz[wson[u]]) && (wson[u] = v);
	}
	int s = wson[u];
	// h[u] = f[u]
	if(s) {
		// upd h[u]
	}
}
struct BST {
	Mat val[N], sum[N]; bool isr[N];
	int fa[N], son[N][2], rt, sta[N], top, n;
	inline void up(int x) {
		sum[x] = val[x];
		if(son[x][0]) sum[x] = sum[son[x][0]] * sum[x];
		if(son[x][1]) sum[x] = sum[x] * sum[son[x][1]];
	}
	inline int sbuild(int l, int r) {
		if(l > r) return 0;
		int tot = 0, now = 0;
		rep(i, l, r + 1) tot += sz[sta[i]] - sz[wson[sta[i]]];
		rep(i, l, r + 1) {
			now += sz[sta[i]] - sz[wson[sta[i]]];
			if((now << 1) >= tot) {
				int x = sta[i];
				son[x][0] = sbuild(l, i - 1);
				son[x][1] = sbuild(i + 1, r);
				fa[son[x][0]] = fa[son[x][1]] = x;
				up(x);
				return x;
			}
		}
	}
	int build(int tp, int f) {
		for(int u = tp; u; f = u, u = wson[u]) {
			for(int i = hd[u]; i; i = ne[i]) if(to[i] != f && to[i] != wson[u]) {
				fa[build(to[i], u)] = u;
			}
			// upd val[u]
		}
		top = 0;
		for(int u = tp; u; u = wson[u]) sta[++top] = u;
		return sbuild(1, top);
	}
	void build(int _n) {
		n = _n; rt = build(1, 0);
		rep(i, 1, n + 1) isr[i] = (son[fa[i]][0] != i && son[fa[i]][1] != i);
	}
	inline int upd(int x, int y) { 
		// upd h[x], a[x] = y, val[x]
		while(x) {
			if(isr[x] && fa[x]) {
				// get old f[x]
				up(x);
				// get new f[x]
				// u = fa[x], get h[u], val[u]
			} else {
				up(x);
			}
			x = fa[x];
		}
		// get dp[1] by sum[rt]
	}
}bst;
void init() {
	dfs(1, 0);
	bst.build(n);
}
