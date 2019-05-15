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

int n, m;
int a[N], b[N], who[N], id[N];
vi g[N];
vi A;

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	map<int, pair<ll, int> > val[N];
	void up(int rt) {
		val[rt] = val[ls];
		map<int, pair<ll, int> >::iterator it = val[rs].begin();
		while(it != val[rs].end()) {
			pair<ll, int> c = val[rt][it->fi];
			c.fi += it->se.fi;
			c.se = max(c.se, it->se.se);
			val[rt][it->fi] = c;
			it++;
		}
	}
	void build(int l, int r, int rt) {
		if(l == r) {
			int p = who[l];
			val[rt][a[p]] = mp(b[p], b[p]);
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void upd(int p, int l, int r, int rt) {
		if(l == r) {
			val[rt].clear();
			int p = who[l];
			val[rt][a[p]] = mp(b[p], b[p]);
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, l, mid, ls);
		else upd(p, mid + 1, r, rs);
		rep(i, 0, sz(::A)) {
			int A = ::A[i];
			ll sum = val[ls][A].fi + val[rs][A].fi;
			int ma = max(val[ls][A].se, val[rs][A].se);
			val[rt][A] = mp(sum, ma);
		}
	}
	pair<ll, int> qry(int L, int R, int A, int l, int r, int rt) {
		if(L <= l && r <= R) {
			if(val[rt].count(A)) return val[rt][A];
			return mp(0, 0);
		}
		int mid = l + r >> 1, ma = 0;
		ll sum = 0; 
		if(L <= mid) {
			pair<ll, int> t = qry(L, R, A, l, mid, ls);
			sum += t.fi;
			ma = max(ma, t.se);
		}
		if(R > mid) {
			pair<ll, int> t = qry(L, R, A, mid + 1, r, rs);
			sum += t.fi;
			ma = max(ma, t.se);
		}
		return mp(sum, ma);
	}
}seg;

// id starts with 1
struct HeavyChain{
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], _, par[N];
	void dfs(int c, int fa, vi g[]){
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
	void dfs2(int c, int fa, vi g[]){
		id[c] = ++_;
		who[_] = c;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c, g);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t != fa && t != s) dfs2(t, c, g);
		}
	}
	pair<ll, int> qry(int a, int b) {
		int A = ::a[a];
		int fa = top[a], fb = top[b];
		ll sum = 0; int ma = 0;
		while(fa != fb) {
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			pair<ll, int> t = seg.qry(id[fa], id[a], A, 1, n, 1); 
			sum += t.fi; ma = max(ma, t.se);
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		pair<ll, int> t = seg.qry(id[b], id[a], A, 1, n, 1);
		sum += t.fi; ma = max(ma, t.se);
		return mp(sum, ma);
	}
	void build(vi g[]){
		dfs(1, 0, g);
		_=0;
		dfs2(1, 0, g);
		seg.build(1, n, 1);
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> b[i] >> a[i];
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	hc.build(g);
	while(m--) {
		string s; int x, y;
		cin >> s >> x >> y;
		if(s[1] == 'C') {
			A.clear();
			A.pb(a[x]);
			a[x] = y;
			A.pb(a[x]);
			seg.upd(id[x], 1, n, 1);
		} else if(s[1] == 'W') {
			A.clear();
			A.pb(a[x]);
			b[x] = y;
			seg.upd(id[x], 1, n, 1);
		} else if(s[1] == 'S') {
			pair<ll, int> ans = hc.qry(x, y);
			cout << ans.fi << endl;
		} else {
			pair<ll, int> ans = hc.qry(x, y);
			cout << ans.se << endl;
		}
	}
	return 0;
}
