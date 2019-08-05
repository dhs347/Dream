#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010, B = 316;

int n, m, col[N], id[N], who[N];
vi g[N];
set<int> st[N];

struct Seg {
	const int N = ::N * 18;
}seg;

struct Blo {
	int ans[N / B + 5][N], res[N], la[N / B + 5];
	void dfs(int u, int fa) {
		int rt = 0;
		for(auto v : g[u]) if(v != fa) {
			dfs(v, u);
		}
	}
	void build() {
		dfs(1, 0);
	}
}blo;

// id starts with 1
struct HeavyChain{
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], _, par[N];
	void dfs(int c, int fa, vi g[]){
		sz[c] = 1;
		par[c] = fa;
		dep[c] = dep[fa] + 1;
		int &s = wson[c] = top[c] = 0;
		for(auto t : g[c]) if(t != fa) {
			dfs(t, c, g);
			sz[c] += sz[t];
			if(sz[t] >= sz[s]) s = t;
		}
	}
	void dfs2(int c, int fa, vi g[]){
		id[c] = ++_;
		who[_] = c;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c, g);
		for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c, g);
	}
	int lca(int a, int b){
		int fa = top[a], fb = top[b];
		while(fa != fb){
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			// Cal id[fa] .. id[a]
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		// Cal id[b] .. id[a]
		// b is lca
		return b;
	}
	void upd(int a, int b, int c) {
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			blo.upd(id[fa], id[a], c);
			a = par[fa], fa = top[a];
		}
		blo.upd(id[b] + 1, id[a]);
	}
	void Build(vi g[]){
		dfs(1, 0, g);
		_=0;
		dfs2(1, 0, g);
	}
}hc;

void solve() {
	cin >> n >> m;
	rep(i, 1, n + 1) g[i].clear(), st[i].clear();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, 1, n + 1) cin >> col[i];
	hc.Build(g);
	rep(i, 1, n + 1) st[col[who[i]]].insert(i);
	blo.build();
	rep(i, 1, m + 1) {
		int o; cin >> o;
		if(o == 1) {
			int u, c; cin >> u >> c;
			int old = col[u], res = 0;
			if(c == old) continue;
			auto pos = st[old].find(id[u]), np = pos;
			if(pos != st[old].begin()) {
				auto t = pos; t--;
				int tt = hc.lca(u, who[*t]);
				if(hc.dep[tt] > hc.dep[res]) res = tt;
			}
			pos++;
			if(pos != st[old].end()) {
				int tt = hc.lca(u, who[*pos]);
				if(hc.dep[tt] > hc.dep[res]) res = tt;
			}
			hc.upd(u, res, -1);
			st[old].erase(np);
			res = 0;
			pos = st[c].lower_bound(id[u]);
			if(pos != st[c].end()) {
				int tt = hc.lca(u, who[*pos]);
				if(hc.dep[tt] > hc.dep[res]) res = tt;
			}
			if(pos != st[c].begin()) {
				pos--;
				int tt = hc.lca(u, who[*pos]);
				if(hc.dep[tt] > hc.dep[res]) res = tt;
			}
			hc.upd(u, res, 1);
			col[u] = c;
			st[c].insert(id[u]);
		} else {
			int k; cin >> k;
			cout << blo.qry(k) << endl;
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
