#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e3 + 7;
int n, k, u, vis[N], p, m, ans1, ans2;
vi tmp, tmp2, g[N];
vector<pii> tmp3;
bitset<N> a[N];
void dfs(int u) {
	vis[u] = 1;
	for (auto v : g[u]) if (!vis[v]) dfs(v); 
}

int main() {
//	freopen("a.in", "r", stdin);
	freopen("hospital.in", "r", stdin);
	freopen("hospital.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> k;
	rep(i, 1, k+1) {
		cin >> m;
		rep(j, 1, m+1) {
			cin >> u;
			g[u].pb(i);
		}
	}		
	rep(i, k+1, n+1) dfs(i);
	rep(i, 1, k+1) if (!vis[i]) {
		ans1++;tmp.pb(i);
	}else tmp2.pb(i);
	cout << ans1 << endl;
	rep(i, 0, sz(tmp)) cout << tmp[i] << " \n"[i == sz(tmp) - 1];
	rep(i, 1, n+1) {
		memset(vis, 0, sizeof(vis));
		vis[i] = 1;
		rep(j, k+1, n+1) if (!vis[j]) dfs(j);
		rep(j, 1, k+1) if (!vis[j] || j == i) a[j][i] = 1;
	}
	rep(i, 0, sz(tmp2)) 
		rep(j, i+1, sz(tmp2)) {
			if ((a[tmp2[i]] & a[tmp2[j]]).any()) tmp3.pb(mp(tmp2[i], tmp2[j]));
		}
	rep(i, 0, sz(tmp2)) 
		rep(j, k+1, n+1) {
			if (a[tmp2[i]][j]) tmp3.pb(mp(tmp2[i], j));
		}
	cout << sz(tmp3) << endl;
	if (sz(tmp3) <= 10000) {
		rep(i, 0, sz(tmp3)) cout << tmp3[i].fi << " " << tmp3[i].se << endl;
	}
	return 0; 
}
