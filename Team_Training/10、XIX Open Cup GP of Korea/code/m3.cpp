#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double db;

const int N = 250000 + 7;
const db eps = 1e-8;

int sign(db x) {
	return (x > eps) - (x < -eps);
}

int n, k; db c;
vector<pii> g[N];
pair<int, db> dp[N][2];

pair<int, db> add(pair<int, db> a, pair<int, db> b) {
	return mp(a.fi + b.fi, a.se + b.se);
}
pair<int, db> sub(pair<int, db> a, pair<int, db> b) {
	return mp(a.fi - b.fi, a.se - b.se);
}
pair<int, db> Max(pair<int, db> a, pair<int, db> b) {
	if(a.se < b.se) swap(a, b);
	if(sign(a.se - b.se) == 0) {
		if(a.fi > b.fi) swap(a, b);
		return a;
	} else {
		return a;
	}
}

void dfs(int u, int fa, db w) {
	dp[u][0] = dp[u][1] = mp(0, 0);
	for(auto v : g[u]) if(v.fi != fa) {
		dfs(v.fi, u, v.se - c);
		dp[u][1] = add(dp[u][1], dp[v.fi][0]);
	}
	dp[u][0] = dp[u][1];
	for(auto v : g[u]) if(v.fi != fa) {
		dp[u][0] = Max(dp[u][0], add(sub(dp[u][1], dp[v.fi][0]), dp[v.fi][1]));
	}
	dp[u][1].fi += 1, dp[u][1].se += w;
}

void solve() {
	dfs(1, 0, -c);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	c = -1e6 * N; solve();
	if(dp[1][0].fi < k) {
		cout << "Impossible" << endl;
		return 0;
	}
	db l = -1e6 * N, r = 1e6 * N, res = 0;
	rep(i, 0, 60) {
		db mid = (l + r) / 2;
		c = mid; solve();
		if(dp[1][0].fi <= k) {
			res = mid;
			r = mid;
		} else {
			l = mid;
		}
	}
	c = res; solve();
	ll ans = dp[1][0].se + res * k + 0.49;
	int st = dp[1][0].fi;
	c = res - 1; solve();
	int ed = dp[1][0].fi;
	if(st <= k && k <= ed) cout << ans << endl;
	else assert(0);
	return 0;
}
