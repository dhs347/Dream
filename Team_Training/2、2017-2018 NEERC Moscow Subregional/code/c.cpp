#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, cnt[22];
vi g[N];
pii ans[N];

int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N];

void dfs(int c, int fa) {
	sz[c] = 1;
	par[c] = fa;
	dep[c] = dep[fa] + 1;
	int &s = wson[c] = top[c] = 0;
	for(auto t : g[c]) if(t != fa) {
		dfs(t, c);
		sz[c] += sz[t];
		if(sz[t] >= sz[s]) s = t;
	}
}

void solve() {
	vi v[22], vec[22];
	v[1].pb(1);
	rep(i, 1, 21) {
		for(auto u : v[i]) {
			while(u) {
				vec[i].pb(u);
				ans[u] = mp(sz(vec[i]), i);
				u = wson[u];
			}
		}
		for(auto u : vec[i]) for(auto t : g[u]) if(t != par[u] && t != wson[u]) v[i + 1].pb(t);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	solve();
	rep(i, 1, n + 1) cout << ans[i].fi << " " << ans[i].se << endl;
	return 0;
}
