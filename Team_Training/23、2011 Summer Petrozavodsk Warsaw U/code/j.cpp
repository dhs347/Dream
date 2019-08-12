#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl '\n'
#define pw(x) (1ll <<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e5 + 10;
const ll inf = pw(50);
ll ansma, f[N][2][2], w[N], d[N];
int u, v, n, siz[N];
vector<pii> g[N];
void dfs(int u, int fa) {
	bool o = 1;
	d[u] = inf;
	for (auto v : g[u]) if (v.fi != fa) {
		o = 0;
		dfs(v.fi, u);
		w[u] += w[v.fi] + 1ll * siz[v.fi] * v.se;
		d[u] = min(d[u], d[v.fi] + v.se);
		siz[u] += siz[v.fi];
	}
	if (o) {
		d[u] = 0;
		siz[u] = 1;
		f[u][1][0] = 0;
		f[u][0][0] = inf;
		f[u][1][1] = inf;
		f[u][0][1] = 0;
	}
	else {
		f[u][1][0] = inf;
		f[u][0][0] = 0;
		f[u][1][1] = f[u][0][1] = inf;
	}
	ll tmp[2][2];
	rep(o1, 0, 2) rep(o2, 0, 2) tmp[o1][o2] = inf;
	
	for (auto v : g[u]) if (v.fi != fa) {
		rep(o1, 0, 2) rep(o2, 0, 2) {
			tmp[o1 ^ o2][0] = min(tmp[o1 ^ o2][0], f[u][o1][0] + f[v.fi][o2][0] + o2 * v.se); 
			if (o1) tmp[o2][1] = min(tmp[o2][1], f[u][o1][0] + f[v.fi][o2][0] + o2 * v.se); 
			if (o2) tmp[o1][1] = min(tmp[o1][1], f[u][o1][0] + f[v.fi][o2][0] + o2 * v.se); 
			tmp[o1 ^ o2][1] = min(tmp[o1 ^ o2][1], f[u][o1][1] + f[v.fi][o2][0] + o2 * v.se); 
			tmp[o1 ^ o2][1] = min(tmp[o1 ^ o2][1], f[u][o1][0] + f[v.fi][o2][1] + o2 * v.se); 
		}
		rep(o1, 0, 2) rep(o2, 0, 2) f[u][o1][o2] = tmp[o1][o2], tmp[o1][o2] = inf;
	}
}

ll dfs2(int u, int fa, int x, int o) {
	int ma = 0, sum = 0, p = 0, ww = 0;
	for (auto v : g[u]) if (v.fi != fa) {
		ma = max(ma, siz[v.fi]);
		if (siz[v.fi] == ma) p = v.fi, ww = v.se;
		sum += siz[v.fi];
	}
	ll res = 0;
	if (sum - ma + x >= ma) {
		for (auto v : g[u]) if (v.fi != fa) res += w[v.fi] + 1ll * v.se * siz[v.fi];
		if (o) res -= d[u];
	}else {
		ll mi = inf;
		for (auto v : g[u]) if (v.fi != fa && siz[v.fi] != ma) mi = min(mi, d[v.fi] + v.se), res += w[v.fi] + 1ll * v.se * siz[v.fi];
		if (!o) {
			res += 1ll * (x + sum - ma) * ww;
			res += dfs2(p, u, x + sum - ma, 0);
		}else {
			res += max(1ll * (x + sum - ma - 1) * ww + dfs2(p, u, x + sum - ma - 1, 0) - mi, 1ll * (x + sum - ma) * ww + dfs2(p, u, x + sum - ma, 1));
		}
	}
	return res;
}




int main() {
	freopen("trams.in", "r", stdin);
	freopen("trams.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	if (n == 1) {
		cout << 0 << endl << 0 << endl;
		return 0;
	}
	if (n == 2) {
		cout << g[1][0].se << endl << g[1][0].se << endl;
		return 0;
	}

	int root = 1;
	rep(i, 1, n+1) if (sz(g[i]) > 1) root = i;
	//de(root);
	dfs(root, 0);
	//rep(i, 1, n+1) de(siz[i]);
	//de(siz[root]);
	cout << f[root][0][siz[root] & 1] << endl;
	cout << dfs2(root, 0, 0, siz[root] & 1) << endl;
	return 0;
}
