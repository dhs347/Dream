/*
 * 带修改莫队：块大小 N^(2/3) 按照 l 所在块， r 所在块， time 排序 
 */
namespace MoOnTree {

	const int N = ::N, SZ = sqrt(N), M = 17;

	int cd; // starts from 1
	int dep[N], pre[N][M], st[N], ed[N], dfn[N << 1], B[N << 1], cnt[N];
	struct Node {
		int l, r, id, lca;
		Node(int id, int l, int r, int lca = 0) : id(id), l(l), r(r), lca(lca) {}
		bool operator < (const Node &c) const {
			if(B[l] != B[c.l]) return B[l] < B[c.l];
			return (r < c.r) ^ (B[l] & 1);
		}
	};
	vector<Node> nds;

	void dfs(int u, int fa, vi g[]) {
		dep[u] = dep[fa] + 1;
		pre[u][0] = fa;
		for(int i = 1; i < M && pre[u][i - 1]; ++i) pre[u][i] = pre[pre[u][i - 1]][i - 1];
		dfn[++cd] = u, st[u] = cd;
		for(auto v : g[u]) if(v != fa) dfs(v, u, g);
		dfn[++cd] = u, ed[u] = cd;
	}
	int lca(int x, int y) {
		if(dep[x] > dep[y]) swap(x, y);
		per(i, 0, M) if(dep[pre[y][i]] >= dep[x]) y = pre[y][i];
		per(i, 0, M) if(pre[x][i] != pre[y][i]) x = pre[x][i], y = pre[y][i];
		if(x == y) return x;
		return pre[x][0];
	}
	void adde(int u, int v, int id) {
		if(st[u] > st[v]) swap(u, v);
		int f = lca(u, v);
		if(f == u) {
			nds.pb(Node(id, st[u], st[v]));
		} else {
			int l = ed[u], r = st[v];
			if(l > r) swap(l, r);
			nds.pb(Node(id, l, r, f));
		}
	}
	// p is index in tree
	void add(int p) {
	}
	void sub(int p) {
	}
	void upd(int p, int c) {
		p = dfn[p];
		cnt[p] += c;
		(cnt[p] == 1) ? add(p) : sub(p);
	}
	void solve(vi g[]) {
		rep(i, 0, N << 1) B[i] = i / SZ;
		dfs(1, cd = 0, g);
		// adde(u, v)
		sort(all(nds));
		int l = 1, r = 0;
		for(auto &nd : nds) {
			while(r < nd.r) upd(++r, 1);
			while(l > nd.l) upd(--l, 1);
			while(r > nd.r) upd(r--, -1);
			while(l < nd.l) upd(l++, -1);
			if(nd.lca) upd(st[nd.lca], 1);
			// save ans
			if(nd.lca) upd(st[nd.lca], -1);
		}
	}
}
