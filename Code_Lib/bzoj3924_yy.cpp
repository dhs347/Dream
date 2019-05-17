#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, m, rt, tot, dfn;
int val[N], par[N], id[N], st[N], ed[N];
ll dp;
ll vfa[N], vch[N];
int sfa[N], sch[N];
vector<pii> g[N];
vector<pair<int, pii> > G[N];

bool vis[N];
int sz[N];

struct FW {
#define lb(x) ((x)&-(x))
	static const int N = ::N;
	int a[N];
	void upd(int p, int c) {
		for( ; p <= n; p += lb(p)) a[p] += c;
	}
	int _qry(int p) {
		int res = 0;
		for( ; p; p ^= lb(p)) res += a[p];
		return res;
	}
	int qry(int l, int r) {
		return _qry(r) - _qry(l - 1);
	}
}fw;

struct LCARMQ {
	static const int N = ::N << 1, M = 20;
	int a[M][N], lft[N], dep[N], lg[N], L, dis[N];
	int rmin(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	void add(int x) {
		a[0][L++] = x;
	}
	void dfs(int c, int fa) {
		lft[c] = L; add(c);
		st[c] = id[c] = ++dfn;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i].fi;
			if(t != fa) {
				dep[t] = dep[c] + 1;
				dis[t] = dis[c] + g[c][i].se;
				dfs(t, c);
				add(c);
			}
		}
		ed[c] = dfn;
	}
	void build() {
		L = 0; dfs(1, 0); dep[0] = -1;
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
		return rmin(a[i][x], a[i][y + 1 - (1 << i)]);
	}
	int Dis(int x, int y) {
		return dis[x] + dis[y] - 2 * dis[lca(x, y)];
	}
}R;

void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	rep(i, 0, sz(g[c])) {
		int t = g[c][i].fi;
		if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
	}
	if(!rt && sz[c] * 2 > Sz) rt = c;
}
int dfs(int c) {
	int rt = 0;
	dfssz(c, 0, 0, rt);
	dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
	rep(i, 0, sz(g[rt])) {
		int v = g[rt][i].fi;
		if(!vis[v]) {
			int t = dfs(v);
			G[rt].pb(mp(t, g[rt][i]));
			par[t] = rt;
		}
	}
	return rt;
}

void upd(int p, int v, int u, int c) {
	if(u == v) {
	} else {
		sfa[u] += c;
		sch[v] += c;
		vfa[u] += c * 1ll * R.Dis(p, u);
		vch[v] += c * 1ll * R.Dis(p, u);
	}
}

ll gao(int u, ll dp, int v, int w) {
	int A, B;
	if(R.dep[u] > R.dep[v]) {
		A = fw.qry(st[u], ed[u]);
		B = tot - A;
	} else {
		B = fw.qry(st[v], ed[v]);
		A = tot - B;
	}
	return dp + (A - B) * 1ll * w;
}

ll qry(int p, int v, int u) {
	if(u == v) {
		return vfa[u];
	} else {
		ll ans = vfa[u] - vch[v] + (sfa[u] + val[u] - sch[v]) * 1ll * R.Dis(u, p);
		return ans;
	}
}

ll qry(int p) {
	int u = p, v = p;
	ll ans = 0;
	while(1) {
		ans += qry(p, v, u);
		if(u == rt) break;
		v = u, u = par[u];
	}
	return ans;
}

ll qry() {
	int now = rt; ll dp = ::dp;
	while(now) {
		//dd(now), de(dp);
		bool find = 0;
		rep(i, 0, sz(G[now])) {
			ll f = gao(now, dp, G[now][i].se.fi, G[now][i].se.se);
			if(f < dp) {
				int u = now, v = G[now][i].fi;
				ll res = qry(v);
				dp = res, now = v;
				find = 1;
				break;
			}
		}
		if(!find) return dp;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w)), g[v].pb(mp(u, w));
	}
	R.build();
	rt = dfs(1);
//	rep(i, 1, n + 1) dd(i), de(par[i]);
	rep(i, 1, m + 1) {
		int x, y;
		cin >> x >> y;
		val[x] += y, tot += y;
		dp += R.Dis(rt, x) * 1ll * y;
		fw.upd(id[x], y);
		int p = x, v = x, u = x;
		while(1) {
			upd(p, v, u, y);
			if(u == rt) break;
			v = u, u = par[u];
		}
		cout << qry() << endl;
	}
	return 0;
}
