#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, m, w[N], id[N], ans[N], ed[N];
vi g[N];
vector<pair<int, pii> > vec, vv[N];

struct Q {
	int x, k, i;
	bool operator < (const Q &c) const {
		return k < c.k;
	}
}q[N];

struct Seg { 
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int ma[N];
	void init() {
		fill_n(ma, n << 2 | 1, 0);
	}
	void upd(int p, int c, int l, int r, int rt) {
		ma[rt] = max(ma[rt], c);
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
	int qry(int L, int R, int l, int r, int rt) {
		if(L > R) return 0;
		if(L <= l && r <= R) return ma[rt];
		int mid = l + r >> 1, ans = 0;
		if(L <= mid) ans = max(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = max(ans, qry(L, R, mid + 1, r, rs));
		return ans;
	}
}seg;

struct HC {
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], _, par[N], who[N];
	void dfs(int c, int fa, vi g[]) {
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
	void dfs2(int c, int fa, vi g[]) {
		id[c] = ++_;
		who[_] = c;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c, g);
		for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c, g);
		ed[c] = _;
	}
	void dfs2(int u, int fa, int l) {
		vec.pb(mp(u - w[l], mp(l, u)));
		for(auto v : g[u]) if(v != fa) dfs2(v, u, l);
	}
	void dfs(int u, int fa) {
		for(auto v : g[u]) if(v != fa && v != wson[u]) dfs2(v, u, u);
		for(auto v : g[u]) if(v != fa) dfs(v, u);
	}
	void build(vi g[]) {
		dfs(1, 0, g);
		_ = 0;
		dfs2(1, 0, g);
		dfs(1, 0);
		sort(all(vec));
	}
	void gao(int l, int r, int k, int ind) {
		if(l > r) return ;
		if(k < 1) return ;
		if(k > n) k = n;
		vv[k].pb(mp(ind, mp(l, r)));
	}
	void qry(int x, int ind, int k) {
		gao(id[x], ed[x], w[x] + k, ind);
		int &res = ans[ind];
		while(x) {
			res = max(res, seg.qry(id[top[x]], id[x] - 1, 1, n, 1));
			int y = top[x];
			x = par[y];
			if(!x) break;
			gao(id[x], id[y] - 1, w[x] + k, ind);
			gao(ed[y] + 1, ed[x], w[x] + k, ind);
		}
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> w[i];
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	hc.build(g);
	rep(i, 1, m + 1) cin >> q[i].x >> q[i].k, q[i].i = i;
	sort(q + 1, q + 1 + m);
	int pos = 0;
	rep(i, 1, m + 1) {
		while(pos < sz(vec) && vec[pos].fi <= q[i].k) seg.upd(id[vec[pos].se.fi], vec[pos].se.se, 1, n, 1), pos++;
		hc.qry(q[i].x, q[i].i, q[i].k);
	}
	seg.init();
	rep(i, 1, n + 1) {
		seg.upd(id[i], i, 1, n, 1);
		for(auto u : vv[i]) {
			int ind = u.fi;
			ans[ind] = max(ans[ind], seg.qry(u.se.fi, u.se.se, 1, n, 1));
		}
	}
	rep(i, 1, m + 1) cout << ans[i] << " \n"[1];
	return 0;
}
