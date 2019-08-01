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

const int N = 202020, M = 20;

int n, m, q, in[N], out[N], fa[M][N], dep[N];
pii Q[N], e[N];
vi g[N];

void add(int u, int v) {
//	dd(u), de(v);
	g[u].pb(v);
	++out[u]; ++in[v];
}

int lca(int x, int y) {
	if(x == 0) return y;
	if(dep[x] > dep[y]) swap(x, y);
	per(i, 0, M) if(dep[fa[i][y]] >= dep[x]) y = fa[i][y];
	per(i, 0, M) if(fa[i][x] != fa[i][y]) x = fa[i][x], y = fa[i][y];
	if(x == y) return x;
	return fa[0][x];
}

void dtr(int ed) {
	rep(i, 0, M) rep(j, 0, ed + 1) fa[i][j] = 0;
	vi que; que.pb(ed); dep[ed] = 1;
	rep(i, 0, sz(que)) {
		int u = que[i];
		for(auto v : g[u]) {
			fa[0][v] = lca(fa[0][v], u);
			--in[v];
			if(in[v] == 0) {
				dep[v] = dep[fa[0][v]] + 1;
				rep(i, 1, M) fa[i][v] = fa[i - 1][fa[i - 1][v]];
				que.pb(v);
			}
		}
	}
}

void solve() {
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		e[i] = mp(u, v);
	}
	cin >> q;
	rep(i, 1, q + 1) {
		int u, v; cin >> u >> v;
		Q[i] = mp(u, v);
	}
	rep(i, 1, n + q + 2) g[i].clear(), in[i] = out[i] = 0;
	rep(i, 1, m + 1) {
		int u = e[i].se, v = e[i].fi;
		add(u, v);
	}
	int ed = n + q + 1;
	rep(i, 1, n + 1) if(!in[i]) {
		add(ed, i);
	}
	rep(i, 1, q + 1) {
		int u = Q[i].fi, v = Q[i].se;
		int w = n + i;
		add(u, w);
		add(v, w);
	}
	dtr(ed);
	rep(i, 1, q + 1) {
		int u = Q[i].fi, v = Q[i].se;
		int ans = dep[u] + dep[v] - 2;
		ans -= dep[i + n] - 2;
		cout << ans << endl;
	}
	rep(i, 0, ed + 1) dep[i] = 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
