#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, m, cntd;
int dfn[N], who[N];
bool vis[N];
set<int> st;
vector<pii> g[N];

void dfs(int u, int fa) {
	dfn[u] = ++cntd;
	who[cntd] = u;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi;
		if(v != fa) {
			dfs(v, u);
		}
	}
}

struct LCARMQ {
	static const int N = ::N << 1, M = 18;
	int a[M][N], lft[N], dep[N], lg[N], L;
	ll dis[N];
	int rmin(int x, int y) {
		return dep[x] < dep[y] ? x : y;
	}
	void add(int x) {
		a[0][L++] = x;
	}
	void dfs(int c, int fa) {
		lft[c] = L; add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i].fi;
			if(t != fa) {
				dep[t] = dep[c] + 1;
				dis[t] = dis[c] + g[c][i].se;
				dfs(t, c);
				add(c);
			}
		}
	}
	void build() {
		L = 0; dfs(1, 0); dep[0] = -1;
		rep(i, 2, L) lg[i] = lg[i >> 1] + 1;
		rep(i, 1, M) {
			int lim = L + 1 - pw(i);
			rep(j, 0, lim) a[i][j] = rmin(a[i - 1][j], a[i - 1][j + (1 << i >> 1)]);
		}
	}
	int lca(int x, int y) {
		x = lft[x], y = lft[y];
		if(x > y) swap(x, y);
		int i = lg[y - x + 1];
		return rmin(a[i][x], a[i][y + 1 - pw(i)]);
	}
	ll Dis(int x, int y) {
		ll ans = dis[x] + dis[y] - 2 * dis[lca(x, y)];
		return ans;
	}
}R;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	dfs(1, 0);
	R.build();
	ll ans = 0;
	while(m--) {
		int x; cin >> x;
		if(!vis[x]) {
			if(sz(st)) {
				set<int>::iterator it = st.lower_bound(dfn[x]);
				int pre, ne;
				ans += R.Dis(x, pre = who[it == st.end() ? *st.begin() : *it]);
				if(it == st.begin()) it = st.end(); --it;
				ans += R.Dis(x, ne = who[*it]);
				ans -= R.Dis(pre, ne);
			}
			st.insert(dfn[x]);
		} else {
			if(sz(st) > 1) {
				set<int>::iterator it = st.find(dfn[x]), pre = (it == st.begin() ? st.end() : it), ne = it;
				--pre; ++ne;
				if(ne == st.end()) ne = st.begin();
				ans += R.Dis(who[*pre], who[*ne]);
				ans -= R.Dis(x, who[*ne]);
				ans -= R.Dis(who[*pre], x);
			}
			st.erase(dfn[x]);
		}
		cout << ans << endl;
		vis[x] ^= 1;
	}
	return 0;
}
