#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1e6 + 7;

int n, d, pre[N];
vi g[N];
int mmd[N];

int vec[N], cntv;
int dep[N], maxdep, md;
vi sx[N], sy[N];

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	x = find(x), y = find(y);
	pre[x] = y;
}
void gao(vi &vec) {
	rep(i, 1, sz(vec)) join(vec[i], vec[i - 1]);
	vec = vi(1, vec[0]);
}
namespace Cen {
	const int N = ::N;
	bool vis[N];
	int sz[N];
	void dfssz(int c, int fa, int Sz, int &rt) {
		sz[c] = 1;
		for(auto t : g[c]) if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
		if(!rt && sz[c] * 2 > Sz) rt = c;
	}
	void dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		vec[++cntv] = u;
		md = max(md, dep[u]);
		if(dep[u] < d) for(auto v : g[u]) if(v != fa && !vis[v]) dfs(v, u);
	}
	void dfs(int c) {
		int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
		vis[rt] = 1;

		maxdep = 0;

		sx[0].pb(rt);
		dep[rt] = 0;
		for(auto u : g[rt]) if(!vis[u]) {
			//de(u);
			cntv = md = 0; dfs(u, rt);
		//	de(u);
			rep(i, 0, md + 1) sy[i].clear();
	//		de(md);
			rep(i, 1, cntv + 1) sy[dep[vec[i]]].pb(vec[i]);
//			de(1);
			rep(i, 1, md + 1) if(d - i <= maxdep && sz(sx[d - i])) {
				gao(sx[d - i]);
				gao(sy[i]);
				join(sx[d - i][0], sy[i][0]);
			}
			rep(i, 0, md + 1) sx[i].insert(sx[i].end(), all(sy[i]));
			maxdep = max(maxdep, md);
			mmd[u] = md;
		}

		rep(i, 0, maxdep + 1) sx[i].clear();

		for(auto t : g[rt]) if(!vis[t] && 2 * mmd[t] >= d) dfs(t);
	}
};

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> d;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	if(d == 0) {
		cout << n << endl;
	} else if(d == 1) {
		cout << 1 << endl;
	} else {
		rep(i, 1, n + 1) pre[i] = i;
		Cen::dfs(1);
		int ans = 0;
		rep(i, 1, n + 1) ans += i == find(i);
		cout << ans << endl;
	}
	return 0;
}
