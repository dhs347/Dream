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

int n, m, rt;
int who[N];
vi g[N];
ll val[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll la[N], mi[N];
	void up(int rt) {
		mi[rt] = min(mi[ls], mi[rs]);
	}
	void build(int l, int r, int rt) {
		la[rt] = 0;
		if(l == r) {
			mi[rt] = val[who[l]];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void gao(int rt, ll c) {
		mi[rt] = la[rt] = c;
	}
	void down(int rt) {
		if(la[rt]) gao(ls, la[rt]), gao(rs, la[rt]);
		la[rt] = 0;
	}
	void upd(int L, int R, ll c, int l, int r, int rt) {
		if(L <= l && r <= R) {
			gao(rt, c);
			return ;
		}
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	ll qry(int L, int R, int l, int r, int rt) {
		if(L > R) return pw(31);
		if(L <= l && r <= R) return mi[rt];
		int mid = l + r >> 1;
		down(rt);
		ll ans = pw(31);
		if(L <= mid) ans = min(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = min(ans, qry(L, R, mid + 1, r, rs));
		up(rt);
		return ans;
	}
}seg;

struct HC {
	static const int N = ::N, M = 22;
	int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], st[N], ed[N], pre[N][M];
	void dfs(int c, int fa, vi g[]) {
		pre[c][0] = fa;
		rep(i, 1, M) pre[c][i] = pre[pre[c][i - 1]][i - 1];
		sz[c] = 1;
		par[c] = fa;
		dep[c] = dep[fa] + 1;
		int &s = wson[c] = top[c] = 0;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t != fa) {
				dfs(t, c, g);
				sz[c] += sz[t];
				if(sz[t] >= sz[s]) s = t;
			}
		}
	}
	void dfs2(int c, int fa, vi g[]) {
		id[c] = ++_;
		who[_] = c;
		st[c] = _;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c, g);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t != fa && t != s) dfs2(t, c, g);
		}
		ed[c] = _;
	}
	int gao(int q, int rt) {
		per(i, 0, M) if(dep[pre[rt][i]] > dep[q]) rt = pre[rt][i];
		return rt;
	}
	int upd(int a, int b, ll c) {
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			if(c) seg.upd(id[fa], id[a], c, 1, n, 1);
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		if(c) seg.upd(id[b], id[a], c, 1, n, 1);
		else return b;
		return 0;
	}
	void build(vi g[]) {
		dfs(1, 0, g);
		_ = 0;
		dfs2(1, 0, g);
		seg.build(1, n, 1);
		dep[0] = -1;
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i, 1, n + 1) cin >> val[i];
	cin >> rt;
	hc.build(g);
	while(m--) {
		int o;
		cin >> o;
		if(o == 1) {
			cin >> rt;
		} else if(o == 2) {
			int a, b; ll c;
			cin >> a >> b >> c;
			hc.upd(a, b, c);
		} else {
			int q;
			cin >> q;
			int l = hc.upd(q, rt, 0);
			if(q == rt) {
				cout << seg.mi[1] << endl;
			} else if(l == q) {
				int t = hc.gao(q, rt);
				ll ans = seg.qry(1, hc.st[t] - 1, 1, n, 1);
				ans = min(ans, seg.qry(hc.ed[t] + 1, n, 1, n, 1));
				cout << ans << endl;
			} else {
				cout << seg.qry(hc.st[q], hc.ed[q], 1, n, 1) << endl;
			}
		}
	}
	return 0;
}
