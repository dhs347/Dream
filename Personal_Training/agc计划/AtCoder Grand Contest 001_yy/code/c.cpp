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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2020;

int n, m;
int f[N], h[N], dep[N];
vi g[N];

void dfs(int u, int fa, int k, int f[]) {
	f[u] = 1;
	for(auto v : g[u]) if(v != fa) {
		int &t = dep[v] = dep[u] + 1;
		if(t <= k) {
			dfs(v, u, k, f);
			f[u] += f[v];
		}
	}
}

int solve(int rt) {
	fill_n(f + 1, n, 0);
	fill_n(h + 1, n, 0);
	dep[rt] = 0;
	dfs(rt, 0, m / 2, f);
	dfs(rt, 0, m - m / 2, h);
	int ans = 0;
	for(auto u : g[rt]) ans += f[u];
	int res = ans;
	for(auto u : g[rt]) res = max(res, ans - f[u] + h[u]);
	res++;
	return res;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	int ans = 0;
	rep(i, 1, n + 1) ans = max(ans, solve(i));
	cout << n - ans << endl;
	return 0;
}
