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

const int N = 1e5 + 5, B = 316;

int n, m, col[N], id[N], who[N], ed[N], dv[N], bst[N], bed[N];
vi g[N];
set<int> st[N];

struct FW {
#define lb(x) (x)&(-(x))
	int a[N];
	void init() { fill_n(a + 1, n, 0); }
	void upd(int p, int c) {
		p = n + 1 - p;
		for( ; p <= n; p += lb(p)) a[p] += c;
	}
	int qry(int p) {
		p = n + 1 - p;
		int ans = 0;
		for( ; p; p ^= lb(p)) ans += a[p];
		return ans;
	}
}fw;

struct Blo {
	int ans[N / B + 5][N << 1], res[N], la[N / B + 5], pre[N];
	vi vec[N];
	void build() {
		rep(i, 1, n + 1) vec[i].clear();
		rep(i, 1, n + 1) vec[ed[i]].pb(i);
		memset(pre, 0, sizeof(pre));
		fw.init();
		rep(i, 1, n + 1) {
			int c = col[who[i]];
			if(pre[c]) fw.upd(pre[c], -1);
			fw.upd(pre[c] = i, 1); 
			for(auto j : vec[i]) {
				res[id[j]] = fw.qry(id[j]);
			}
		}
		memset(ans, 0, sizeof(ans));
		memset(la, 0, sizeof(la));
		rep(i, 1, n + 1) ans[dv[i]][res[i]]++;
		rep(i, 1, n + 1) {
			if(i == 1 || dv[i] != dv[i - 1]) bst[dv[i]] = i;
			if(i == n || dv[i] != dv[i + 1]) bed[dv[i]] = i;
		}
	}
	void down(int b) {
		if(!la[b]) return ;
		rep(i, bst[b], bed[b] + 1) --ans[b][res[i]], res[i] += la[b], ++ans[b][res[i]];
		la[b] = 0;
	}
	void gao(int l, int r, int c) {
		int b = dv[l];
		rep(i, l, r + 1) --ans[b][res[i]], res[i] += c, ++ans[b][res[i]];
	}
	void upd(int l, int r, int c) {
		if(l > r) return ;
		rep(i, dv[l] + 1, dv[r]) la[i] += c;
		down(dv[l]);
		if(dv[l] != dv[r]) down(dv[r]);
		gao(l, min(bed[dv[l]], r), c);
		if(dv[l] != dv[r]) gao(bst[dv[r]], r, c);
	}
	int qry(int k) {
	//	if(k < 1 || k > n) return 0;
		int r = 0;
		rep(i, dv[1], dv[n] + 1) {
			if(k - la[i] >= 0) r += ans[i][k - la[i]];
		}
		return r;
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
		ed[c] = _;
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
		if(a == b) return ;
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			blo.upd(id[fa], id[a], c);
			a = par[fa], fa = top[a];
		}
		blo.upd(id[b] + 1, id[a], c);
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
	rep(i, 0, N) dv[i] = i / B;
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
