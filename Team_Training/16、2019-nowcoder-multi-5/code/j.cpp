#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
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

int n, q, ls[N << 1], rs[N << 1], val[N << 1], m, f[N << 1], h[N << 1], par[20][N], fdis[N << 1], hdis[N << 1]; 
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
			rep(j, 0, lim) a[i][j] = rmin(a[i - 1][j], a[i - 1][j + (1 << i >> 1)]);
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
		if(x > dis(u, v)) return u;
		if(dep[u] - dep[l] >= x) {
			return go(u, x);
		} else {
			return go(v, dis(u, v) - x);
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
	int ans[3];
	void calc() {
		int s = (a + b + c);
		s >>= 1;
		i = s - a, j = s - b, k = s - c;
		if(i < 0) i = 0; if(i > n - 1) i = n - 1;
		if(j < 0) j = 0; if(j > n - 1) j = n - 1;
		if(k < 0) k = 0; if(k > n - 1) k = n - 1;
		int t[] = {i, j, k}; sort(t, t + 3);
		i = t[0], j = t[1], k = t[2];
		ans[0] = ans[1] = ans[2] = 1;
	}
	void print() {
		sort(ans, ans + 3);
		do {
			if(R.dis(ans[0], ans[1]) == a && R.dis(ans[0], ans[2]) == b && R.dis(ans[1], ans[2]) == c) {
				rep(i, 0, 3) cout << ans[i] - 1 << " \n"[i == 2];
				return ;
			}
		} while(next_permutation(ans, ans + 3));
		cout << -1 << endl;
	}
	void set(int x) {
		if(vec[x].dis[0] >= i && vec[x].dis[1] >= j && vec[x].dis[2] >= k) {
			ans[0] = R.go(vec[x].nd[0], vec[x].ver, vec[x].dis[0] - i);
			ans[1] = R.go(vec[x].nd[1], vec[x].ver, vec[x].dis[1] - j); 
			ans[2] = R.go(vec[x].nd[2], vec[x].ver, vec[x].dis[2] - k); 
		} else {
			assert(0);
		}
	}
}qq[N];
struct P {
	int x, y, z, i;
	P() {}
	P(int x, int y, int z, int i) : x(x), y(y), z(z), i(i) {}
	bool operator < (const P &c) const {
		if(x != c.x) return x > c.x;
		if(y != c.y) return y > c.y;
		return i < c.i;
	}
};
vector<P> ps;

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
void dfs(int u) {
	if(u <= n) {
		f[u] = u;
		fdis[u] = 0;
	} 
	if(ls[u]) {
		dfs(ls[u]);
		f[u] = f[ls[u]];
		fdis[u] = fdis[ls[u]] + val[ls[u]];
	}
	if(rs[u]) {
		dfs(rs[u]);
		int t = f[rs[u]];
		int tt = fdis[rs[u]] + val[rs[u]];
		if(fdis[u] < tt) f[u] = t, fdis[u] = tt;
	}
}
void dfs2(int u, int fa) {
	if(u <= n) {
		h[u] = u;
		hdis[u] = 0;
	}
	if(fa) {
		h[u] = h[fa];
		hdis[u] = hdis[fa] + val[u];
		if(ls[fa] && rs[fa] == u) {
			int s = ls[fa];
			int tt = fdis[s] + val[s] + val[u];
			if(hdis[u] < tt) h[u] = f[s], hdis[u] = tt;
		}
		if(rs[fa] && ls[fa] == u) {
			int s = rs[fa];
			int tt = fdis[s] + val[s] + val[u];
			if(hdis[u] < tt) h[u] = f[s], hdis[u] = tt;
		}
	}
	if(ls[u]) dfs2(ls[u], u);
	if(rs[u]) dfs2(rs[u], u);
}
struct Fenwick {
#define lb(x) (x)&(-(x))
	int a[N], b[N];
	void init() { fill_n(a, n, -1); }
	void upd(int p, int c, int i) {
		p = n - p;
		for(; p <= n; p += lb(p)) if(a[p] < c) a[p] = c, b[p] = i;
	}
	int qry(int p, int c) {
		p = n - p;
		for(; p; p ^= lb(p)) if(a[p] >= c) return b[p];
		return -1;
	}
}fw;

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
	dfs(1);
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
		if(u != h[u]) tmp.pb(mp(0, u));
		sort(all(tmp));
		reverse(all(tmp));
		if(sz(tmp) >= 3) {
			vec.pb(Node(u, tmp[2].se, tmp[1].se, tmp[0].se, tmp[2].fi, tmp[1].fi, tmp[0].fi));
		}
	}
	fw.init();
	rep(i, 0, sz(vec)) {
		ps.pb(P(vec[i].dis[0], vec[i].dis[1], vec[i].dis[2], -i));
	}
	rep(i, 1, q + 1) ps.pb(P(qq[i].i, qq[i].j, qq[i].k, i));
	sort(all(ps));
	for(auto p : ps) {
		if(p.i > 0) {
			int x = fw.qry(p.y, p.z);
			if(x >= 0) qq[p.i].set(x);
		} else {
			fw.upd(p.y, p.z, -p.i);
		}
	}
	rep(i, 1, q + 1) qq[i].print();
	return 0;
}
