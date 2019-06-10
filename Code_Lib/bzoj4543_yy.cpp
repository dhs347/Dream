#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, wson[N], dep[N], id[N], who[N], _, f[N];
vi g[N];
ll ans, F[N << 1];

void dfs(int c, int fa) {
	dep[c] = 0; int &s = wson[c] = 0;
	rep(i, 0, sz(g[c])) {
		int t = g[c][i];
		if(t != fa) {
			dfs(t, c), dep[c] = max(dep[t] + 1, dep[c]), (dep[t] >= dep[s]) && (s = t);
		}
	}
}
void dfs2(int c, int fa) {
	who[id[c] = ++_] = c;
	int s = wson[c];
	if(s) dfs2(s, c);
	rep(i, 0, sz(g[c])) {
		int t = g[c][i];
		if(t != fa && t != s) dfs2(t, c);
	}
}
int cf(int u, int i) {
	if(i < 0 || i > dep[u]) return 0;
	return id[u] + i;
}
int cF(int u, int i) {
	if(i < 0 || i > dep[u]) return 0;
	return dep[u] - i + id[u] * 2;
}
void solve(int c, int fa) {
	rep(i, 0, sz(g[c])) {
		int t = g[c][i];
		if(t != fa) solve(t, c);
	}
	int s = wson[c];
	if(s) {
		if(dep[s]) ans += F[cF(s, 1)];
		f[cf(c, 0)] = 1;
	} else {
		f[cf(c, 0)] = 1;
	}
	rep(_, 0, sz(g[c])) {
		int t = g[c][_];
		if(t != fa && t != s) {
			rep(i, 0, dep[t] + 1) {
				ans += f[cf(t, i)] * 1ll * F[cF(c, i + 1)];
				if(i) ans += f[cf(c, i - 1)] * 1ll * F[cF(t, i)];
			}
			rep(i, 1, dep[t] + 1) {
				F[cF(c, i - 1)] += F[cF(t, i)];
			}
			rep(i, 0, dep[t] + 1) {
				F[cF(c, i + 1)] += f[cf(c, i + 1)] * 1ll * f[cf(t, i)];
			}
			rep(i, 0, dep[t] + 1) {
				f[cf(c, i + 1)] += f[cf(t, i)];
			}
		}
	}
//	ans += F[cF(c, 0)];
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
	dfs2(1, 0);
	solve(1, 0);
	cout << ans << endl;
	return 0;
}
