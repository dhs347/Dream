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

const int N = 404040, inf = 1e9;

int n, ls[N], rs[N], val[N], f[N][2], h[N][2];
vector<pii> g[N];

void add(int u, int v, int w) {
	val[v] = w;
	if(!ls[u]) {
		ls[u] = v;
	} else {
		rs[u] = v;
	}
}

void Ma(int &a, int b) {
	if(a < b) a = b;
}
void Mi(int &a, int b) {
	if(a > b) a = b;
}

void dfs(int u, int fa) {
	if(ls[u]) dfs(ls[u], u);
	if(rs[u]) dfs(rs[u], u);
	f[u][0] = 0;
	if(ls[u]) Ma(f[u][0], f[ls[u]][0] + val[ls[u]]);
	if(rs[u]) Ma(f[u][0], f[rs[u]][0] + val[rs[u]]);
	f[u][1] = inf;
	if(ls[u]) {
		int t = 0;
		if(ls[u]) Ma(t, min(f[ls[u]][0], f[ls[u]][1] + val[ls[u]]));
		if(rs[u]) Ma(t, f[rs[u]][0] + val[rs[u]]);
		Mi(f[u][1], t);
	}
	if(rs[u]) {
		int t = 0;
		if(ls[u]) Ma(t, f[ls[u]][0] + val[ls[u]]);
		if(rs[u]) Ma(t, min(f[rs[u]][0], f[rs[u]][1] + val[rs[u]]));
		Mi(f[u][1], t);
	}
}

void dfs2(int u, int fa) {
	h[u][0] = 0;
	h[u][1] = inf;
	if(fa) {
		Ma(h[u][0], h[fa][0]);
		if(ls[fa] && rs[fa] == u) {
			int s = ls[fa];
			Ma(h[u][0], f[s][0] + val[s]);
		}
		if(rs[fa] && ls[fa] == u) {
			int s = rs[fa];
			Ma(h[u][0], f[s][0] + val[s]);
		}
		h[u][1] = h[u][0]; // del(u, fa)
		h[u][0] += val[u];
		// del(fa)
		int t = h[fa][1];
		if(ls[fa] && rs[fa] == u) {
			int s = ls[fa];
			Ma(t, f[s][0] + val[s]);
		}
		if(rs[fa] && ls[fa] == u) {
			int s = rs[fa];
			Ma(t, f[s][0] + val[s]);
		}
		Mi(h[u][1], t + val[u]);
		// del(other s);
		t = h[fa][0];
		if(ls[fa] && rs[fa] == u) {
			int s = ls[fa];
			Ma(t, min(f[s][0], f[s][1] + val[s]));
		}
		if(rs[fa] && ls[fa] == u) {
			int s = rs[fa];
			Ma(t, min(f[s][0], f[s][1] + val[s]));
		}
		Mi(h[u][1], t + val[u]);
	}
	if(ls[u]) dfs2(ls[u], u);
	if(rs[u]) dfs2(rs[u], u);
}

void rebuild(int u, int fa) {
	bool F = 0; int pre = u;
	rep(i, 0, sz(g[u])) {
		auto t = g[u][i];
		if(t.fi == fa) continue;
		int v = t.fi, w = t.se;
		if(F) {
			if(i != sz(g[u]) - 1) {
				add(pre, ++n, 0);
				add(n, v, w);
				pre = n;
			} else {
				add(pre, v, w);
			}
		} else {
			add(u, v, w);
			F = 1;
		}
		rebuild(v, u);
	}
}

void solve() {
	cin >> n;
	int nn = n;
	rep(i, 1, n + 1) g[i].clear();
	fill_n(ls + 1, n << 1, 0);
	fill_n(rs + 1, n << 1, 0);
	fill_n(val + 1, n << 1, 0);
	rep(i, 1, n) {
		int u, v, w; cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	rebuild(1, 0);
	dfs(1, 0);
	dfs2(1, 0);
	//rep(i, 1, n + 1) dd(i), dd(h[i][0]), de(h[i][1]);
	int ans = inf, p = 0;
	rep(i, 1, nn + 1) {
		int res = max(f[i][0], h[i][1]);
		Mi(res, max(f[i][1], h[i][0]));
		if(res < ans) {
			ans = res;
			p = i;
		}
	}
	cout << p << " " << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
