#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;

int n, q, ls[N << 1], rs[N << 1], val[N << 1], m, f[N << 1], h[N << 1], par[20][N];
vi g[N];

struct LCARMQ {
	static const int N = ::N << 1;
	int a[20][N], lft[N], dep[N], lg[N], L;
	int rmin(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	void add(int x) {
		a[0][L++] = x;
	}
	void dfs(int c, int fa, const vi g[]) {
		lft[c] = L; add(c);
		par[0][c] = fa;
		rep(i, 1, 20) par[i][c] = par[i - 1][par[i - 1][c]];
		for(auto t : g[c]) if(t != fa) dep[t] = dep[c] + 1, dfs(t, c, g), add(c);
	}
	void build(const vi g[]) {
		L = 0; dfs(1, 0, g); dep[0] = -1;
		rep(i, 2, L) lg[i] = lg[i >> 1] + 1;
		rep(i, 1, 20) {
			int lim = L + 1 - (1 << i);
			rep(j, 0, lim) a[i][j] = rmin(a[i - 1][j], a[i - 1] [j + (1 << i >> 1)]);
		}
	}
	int lca(int x, int y) {
		x = lft[x], y = lft[y];
		if(x > y) swap(x, y);
		int i = lg[y - x + 1];
		return rmin(a[i][x], a[i][y + 1 - pw(i)]);
	}
	int dis(int x, int y) {
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}
	int go(int u, int k) {
		rep(i, 0, 20) if(k >> i & 1) u = par[i][u];
		return u;
	}
	// from u to v go x
	int go(int u, int v, int x) {
		int l = lca(u, v);
		if(dep[u] - dep[l] >= x) {
			return go(u, x);
		} else {
			return go(dep[u] + dep[v] - 2 * dep[l] - x);
		}
	}
}R;
struct Node {
	int ver, nd[3], dis[3];
	Node() {}
	Node(int v, int a, int b, int c, int x, int y, int z) {
		ver = v;
		nd[0] = a, nd[1] = b, nd[2] = c;
		dis[0] = x, dis[1] = y, dis[2] = z;
	}
};

vector<Node> vec;

struct Q {
	int a, b, c, i, j, k;
	int ans[3]; bool oks;
	void calc() {
		oks = 1;
		int s = (a + b + c);
		if(s & 1) oks = 0;
		s >>= 1;
		i = s - a, j = s - b, k = s - c;
		if(i < 0 || j < 0 || k < 0) oks = 0;
		int t[] = {i, j, k};
		sort(t, t + 3);
		i = t[0], j = t[1], k = t[2];
	}
	void print() {
		sort(ans, ans + 3);
	}
}qq[N];

void add(int u, int v, int w) {
	if(!ls[u]) {
		ls[u] = v;
	} else {
		rs[u] = v;
	}
	val[v] = w;
}
void rebuild(int u, int fa) {
	if(fa == 0) m = n;
	bool F = 0; int pre = u;
	rep(i, 0, sz(g[u])) if(g[u][i] != fa) {
		int v = g[u][i];
		if(F) {
			if(i != sz(g[u]) - 1) {
				add(pre, ++m, 0);
				add(m, v, 1);
				pre = m;
			} else {
				add(pre, v, 1);
			}
		} else {
			add(u, v, 1);
			F = 1;
		}
		rebuild(v, u);
	}
}
int dis(int u, int v, int s) {
	if(u <= n) return R.dis(u, v);
	return R.dis(s, v) + 1;
}
int dis2(int u, int fa, int v) {
	if(u <= n) return R.dis(u, v);
	return R.dis(fa, v);
}
void dfs(int u, int fa) {
	f[u] = (u <= n ? u : 0);
	if(ls[u]) {
		dfs(ls[u], u);
		f[u] = f[ls[u]];
	}
	if(rs[u]) {
		dfs(rs[u], u);
		int t = f[rs[u]];
		if(dis(u, f[u], ls[u]) < dis(u, t, rs[u])) f[u] = t;
	}
}
void dfs2(int u, int fa) {
	h[u] = (u <= n ? u : 0);
	if(fa) {
		h[u] = h[fa];
		if(ls[fa] && rs[fa] == u) {
			int s = ls[fa];
			if(dis2(u, fa, h[u]) < dis2(u, fa, f[s])) h[u] = f[s];
		}
		if(rs[fa] && ls[fa] == u) {
			int s = rs[fa];
			if(dis2(u, fa, h[u]) < dis2(u, fa, f[s])) h[u] = f[s];
		}
	}
	if(ls[u]) dfs2(ls[u], u);
	if(rs[u]) dfs2(rs[u], u);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v; cin >> u >> v; ++u, ++v;
		g[u].pb(v); g[v].pb(u);
	}
	rebuild(1, 0);
	R.build(g);
	dfs(1, 0);
	dfs2(1, 0);
	cin >> q;
	rep(i, 1, q + 1) {
		cin >> qq[i].a >> qq[i].b >> qq[i].c;
		qq[i].calc();
	}
	rep(u, 1, n + 1) {
		vector<pii> tmp;
		for(auto v : g[u]) if(v != par[0][u]) {
			tmp.pb(mp(R.dis(f[v], u), f[v]));
		}
		tmp.pb(mp(R.dis(h[u], u), h[u]));
		sort(all(tmp));
		reverse(all(tmp));
		if(sz(tmp) >= 3) {
			vec.pb(Node(u, tmp[0].se, tmp[1].se, tmp[2].se, tmp[0].fi, tmp[1].fi, tmp[2].fi));
		}
	}
	return 0;
}
