#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 7;

int n, q, a[N], par[N], dep[N];
ll ans[N];
vi g[N];
vector<pii> vec[N];

int cntn;
int rt[N], ls[N * 20], rs[N * 20]; 
ll sum[N * 20];

void dfs(int u, int fa) {
	par[u] = fa;
	dep[u] = dep[fa] + 1;
	for(auto v : g[u]) if(v != fa) dfs(v, u);
}
void solve(int u, int fa) {
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	cin >> q;
	rep(i, 1, q + 1) {
		int v, k; cin >> v >> k; int u = v;
		while(k >= 0 && v) {
			if(u == v) {
				vec[v].pb(mp(i, k));
			} else {
				vec[v].pb(mp(i, k));
				if(k) vec[u].pb(mp(-i, k - 1));
			}
			u = v, v = par[v], --k;
		}
	}
	solve(1, 0);
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
