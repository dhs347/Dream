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

const int N = 1e6 + 7;

int n, sz[N], ma[N], dis[N], sz2[N], par[N];
ll ans[N];
vi g[N];

void dfs2(int u, int fa) {
	for(auto v : g[u]) if(v != fa) {
		dis[v] = dis[u] + 1;
		dfs2(v, u);
	}
}
void dfs(int u, int fa, int &ma) {
	ma = max(ma, dis[u]);
	for(auto v : g[u]) if(v != fa) dfs(v, u, ma);
}
void solve(int rt) {
	dis[rt] = 0; dfs2(rt, 0);
	ll &res = ans[rt] = 0;
	int ma = 0;
	rep(i, 1, n + 1) res += dis[i], ma = max(ma, dis[i]);
	if(::ma[rt] == n / 2 && n % 2 == 0) {
		ma = 0;
		for(auto u : g[rt]) {
			int k = 0;
			if(u == par[rt]) {
				k = n - sz[rt];
			} else {
				k = sz[u];
			}
			if(k == n / 2) dfs(u, rt, ma);
		}
	}
	res = res * 2 - ma;
}

void dfs(int u, int fa) {
	par[u] = fa;
	sz[u] = 1;
	for(auto v : g[u]) if(v != fa) {
		dfs(v, u);
		sz[u] += sz[v];
		ma[u] = max(ma[u], sz[v]);
	}
	ma[u] = max(ma[u], n - sz[u]);
}

int main() {
	freopen("inspection.in", "r", stdin);
	freopen("inspection.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, 1, n + 1) ans[i] = -1;
	dfs(1, 0);
	rep(i, 1, n + 1) if(ma[i] <= n / 2) solve(i);
	rep(i, 1, n + 1) cout << ans[i] << endl;
	return 0;
}
