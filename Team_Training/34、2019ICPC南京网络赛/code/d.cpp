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

const db inf = pw(60);
const int N = 1e5+ 67;
int T, n, m, u, v;
vi g[N];

db dp[N], dp2[N];

pair<db, db> dfs(int u) {
	if (u == n) return mp(0, 0);
	if (dp[u] >= 0) return mp(dp2[u], dp[u]);
	dp[u] = 0; dp2[u] = 0;
	for (auto v : g[u]) {
		auto t = dfs(v);
		dp[u] += t.se;
		dp2[u] += t.fi + t.se;
	}
	dp[u] += sz(g[u]) + 1;
	dp[u] /= sz(g[u]);
	dp2[u] += sz(g[u]) + 1 + dp[u];
	dp2[u] /= sz(g[u]);
	return mp(dp2[u], dp[u]);
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, m+1) {
			cin >> u >> v;
			g[u].pb(v);
		}
		rep(i, 1, n+1) dp[i] = -inf, dp2[i] = -inf;
		//cout << dfs(1);
		printf("%.2f\n", dfs(1).fi);
		//rep(i, 1, n+1) de(dp[i]);
	}
	return 0;
}
