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
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 505050;

int n, a[N], dep[N], dp[N], p[N], deg[N], par[N];
vi g[N];

void dfs(int u, int fa) {
	dp[u] = min(dp[u], 1 - dep[u] - a[u]);
	par[u] = fa;
	for(auto v : g[u]) if(v != fa) {
		dep[v] = dep[u] + 1;
		dp[v] = dp[u];
		dfs(v, u);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i ,1, n){
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, 1, n + 1) dp[i] = 2e9;
	dfs(1, 0);
	priority_queue<pii> que;
	rep(i, 2, n + 1) if(sz(g[i]) == 1) que.push(mp(-dp[i], i));
	rep(i, 1, n + 1) deg[i] = sz(g[i]) - (i != 1);
	int pos = 0;
	while(!que.empty()) {
		auto u = que.top(); que.pop();
		p[u.se] = ++pos;
		int v = par[u.se];
		if(v) {
			--deg[v]; if(deg[v] == 0) que.push(mp(-dp[v], v));
		}
	}
	int ans = 0;
	rep(i, 1, n + 1) ans = max(ans, p[i] - 1 + dep[i] + a[i]);
	cout << ans << endl;
	return 0;
}
