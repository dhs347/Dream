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

int n, m, k;
int par[N], dep[N], dis[N];
ll ans;
bool vis[N], inc[N];
vi g[N], G[N], cir;

struct FW {
#define lb(x) ((x)&-(x))
	static const int N = ::N;
	int n, a[N], tot;
	void init(int _n) {fill_n(a + 1, n = _n, 0); tot = 0;}
	void upd(int p, int c) {
		for( ; p <= n; p += lb(p)) a[p] += c;
		tot += c;
	}
	int _qry(int p) {
		int ans = 0;
		for( ; p; p ^= lb(p)) ans += a[p];
		return ans;
	}
	int qry(int p) {
		if(p > n) return 0;
		if(p <= 1) return tot;
		return tot - _qry(p - 1);
	}
}fw;

// id starts from 1
namespace Centriod {
	const int N = ::N;
	bool vis[N];
	int sz[N];
	int md;
	vector<pii> vec[N];
	void dfssz(int c,int fa,int Sz,int &rt,vi g[]){
		sz[c] = 1;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt,g) , sz[c]+=sz[t];
		}
		if(!rt && sz[c]*2>Sz) rt=c;
	}
	void dfs(int u, int fa, int dep, vi g[], int rt) {
		vec[rt].pb(mp(u, dep));
		md = max(md, dep);
		rep(i, 0, sz(g[u])) {
			int v = g[u][i];
			if(!vis[v] && v != fa) dfs(v, u, dep + 1, g, rt);
		}
	}
	void dfs(int c, vi g[]){
		int rt=0;dfssz(c,0,0,rt,g);dfssz(c,0,sz[c],rt=0,g);
		vis[rt] = true;
		/*
		 * 注意计算以 rt 为起点的路径、只包含 rt 的路径
		 * 注意 v != vis[rt] 
		 */
		md = 0;
		rep(i, 0, sz(g[rt])) {
			int v = g[rt][i];
			if(!vis[v]) {
				vec[v].clear();
				dfs(v, rt, 2, g, v);
			}
		}
		fw.init(md);
		fw.upd(1, 1);
		rep(i, 0, sz(g[rt])) {
			int v = g[rt][i];
			if(!vis[v]) {
				rep(j, 0, sz(vec[v])) {
					ans += fw.qry(k - (vec[v][j].se - 1));
				}
				rep(j, 0, sz(vec[v])) {
					fw.upd(vec[v][j].se, 1);
				}
			}
		}
		rep(i, 0, sz(g[rt])) {
			int t = g[rt][i];
			if(!vis[t]) dfs(t, g);
		}
	}
};

void dfs(int u, int fa) {
	vis[u] = 1;
	par[u] = fa;
	dep[u] = dep[fa] + 1;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if(v == fa) continue;
		if(vis[v]) {
			if(dep[v] > dep[u]) continue;
			cir.pb(v);
			inc[v] = 1;
			int t = u;
			while(t != v) {
				cir.pb(t);
				inc[t] = 1;
				t = par[t];
			}
		} else {
			G[u].pb(v);
			G[v].pb(u);
			dfs(v, u);
		}
	}
}

vi vec;

void dfs3(int u, int fa) {
	fw.upd(dis[u], -1);
	vec.pb(dep[u]);
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if(v != fa && !inc[v]) dep[v] = dep[u] + 1, dfs3(v, u);
	}
}

void solve(int u, int d) {
	vec.clear();
	dep[u] = d;
	dfs3(u, 0);
	rep(i, 0, sz(vec)) ans += fw.qry(k - vec[i]);
}

void solve() {
	memset(dis, 0x3f, sizeof(dis));
	dis[cir[0]] = 1;
	vi q; q.pb(cir[0]);
	rep(i, 0, sz(q)) {
		int u = q[i];
		rep(j, 0, sz(G[u])) {
			int v = G[u][j];
			if(dis[v] > dis[u] + 1) {
				dis[v] = dis[u] + 1;
				q.pb(v);
			}
		}
	}
	fw.init(n);
	rep(i, 1, n + 1) fw.upd(dis[i], 1);
	rep(i, 1, sz(cir)) solve(cir[i], i);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	rep(i, 1, m + 1) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	dfs(1, 0);
	Centriod::dfs(1, G);
	if(n == m) solve();
	cout << ans << endl;
	return 0;
}
