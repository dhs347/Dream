#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2020, P = 1e9 + 7;

int n, m, a[N], ans;
vi g[N];
map<int, int> st[N];
map<int, int> s;

void dfs(int u, int fa) {
	st[u].clear();
	st[u][a[u]] = 1;
	for(auto v : g[u]) if(v != fa) {
		dfs(v, u);
		s.clear();
		for(auto t : st[v]) {
			ans += t.se; if(ans >= P) ans -= P;
			for(auto c : st[u]) {
				ll _ = c.fi * 1ll * t.fi;
				if(_ > m) break;
				(s[_] += c.se * 1ll * t.se % P) %= P;
			}
		}
		st[v].clear();
		for(auto t : s) {
			(st[u][t.fi] += t.se) %= P;
		}
	}
}

void solve() {
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> a[i], g[i].clear();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	ans = 0;
	dfs(1, 0);
	for(auto u : st[1]) if((ans += u.se) >= P) ans -= P;
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
