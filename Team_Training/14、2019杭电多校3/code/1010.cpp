#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010, P = 1e9 + 7;

int n, f[N], g[N];
vi h[N];

struct FW {
	static const int N = ::N;
	int n; ll a[N];
	void ini(int _n) {
		n = _n;
		fill_n(a + 1, n, 0);
	}
	void upd(int p, ll c) {
		for(; p <= n; p += (p & -p)) a[p] += c;
	}
	ll _qry(int p) {
		ll res = 0;
		for(; p; p -= (p & -p)) res += a[p];
		return res;
	}
	ll qry(int l, int r) {
		return _qry(r) - _qry(l - 1);
	}
}fw;

struct HC {
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N];
	void dfs(int c, int fa, vi g[]) {
		sz[c] = 1;
		par[c] = fa;
		dep[c] = dep[fa] + 1;
		int &s = wson[c] = top[c] = 0;
		for(auto t : g[c]) if(t != fa) {
			dfs(t, c, g);
			sz[c] += sz[t];
			if(sz[t] >= sz[s]) s = t;
		}
	}
	void dfs2(int c, int fa, vi g[]) {
		id[c] = ++_;
		who[_] = c;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c, g);
		for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c, g);
	}
	void Build(vi g[]) {
		dfs(1, 0, g);
		_ = 0;
		dfs2(1, 0, g);
	}
	vector<pii> get(int uu, int vv) {
		u = uu; v = vv;
		while (u != v) {
			if (dep[u])
		}
	}
}hc;

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> f[i];
	rep(i, 1, n + 1) cin >> g[i];
	rep(i, 1, n + 1) h[i].clear();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		h[u].pb(v);
		h[v].pb(u);
	}
	int q; cin >> q;
	while(q--) {
		int o;
		cin >> o;
		if(o == 1) {
			int s, t, x; cin >> s >> t >> x;
		} else {
			int c, v; cin >> c >> v;
		}
	}
	hc.Build(h);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
