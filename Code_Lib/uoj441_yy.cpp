#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define ls rt << 1
#define rs ls | 1
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;
const ll inf = 1e18;

int n, m;
int a[N];
string op;
vi g[N];

int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N], leaf[N];
ll f[N][2], F[N][2];
struct Mat {
	ll a[2][2];
	inline Mat operator * (const Mat &c) const {
		Mat r; 
		r.a[0][0] = min(a[0][0] + c.a[0][0], a[0][1] + c.a[1][0]);
		r.a[0][1] = min(a[0][0] + c.a[0][1], a[0][1] + c.a[1][1]);
		r.a[1][0] = min(a[1][0] + c.a[0][0], a[1][1] + c.a[1][0]);
		r.a[1][1] = min(a[1][0] + c.a[0][1], a[1][1] + c.a[1][1]);
		return r;
	}
	inline void e() { rep(i, 0, 2) rep(j, 0, 2) a[i][j] = (i != j) * inf; }
};
struct Seg {
	Mat m[N << 2];
	inline void build(int l, int r, int rt) {
		if(l == r) {
			int u = who[l], s = wson[u];
			F[u][1] = a[u];
			rep(i, 0, sz(g[u])) {
				int v = g[u][i];
				if(v != par[u] && v != s) {
					F[u][0] += f[v][1];
					F[u][1] += min(f[v][0], f[v][1]);
				}
			}
			f[u][0] = f[s][1] + F[u][0];
			f[u][1] = min(f[s][0], f[s][1]) + F[u][1];
			m[rt].a[0][0] = inf;
			m[rt].a[0][1] = F[u][0];
			m[rt].a[1][0] = m[rt].a[1][1] = F[u][1];
			return ;
		}
		int mid = l + r >> 1; build(mid + 1, r, rs); build(l, mid, ls);
		m[rt] = m[ls] * m[rs];
	}
	inline void upd(int u, int l, int r, int rt) {
		if(l == r) {
			m[rt].a[0][1] = F[u][0];
			m[rt].a[1][0] = m[rt].a[1][1] = F[u][1];
			return ;
		}
		int mid = l + r >> 1;
		(id[u] <= mid) ? upd(u, l, mid, ls) : upd(u, mid + 1, r, rs);
		m[rt] = m[ls] * m[rs];
	}
	inline void qry(int L, int R, int l, int r, int rt, Mat &ans) {
		if(rt == 1) ans.e();
		if(L <= l && r <= R) return ans = ans * m[rt], void();
		int mid = l + r >> 1;
		if(L <= mid) qry(L, R, l, mid, ls, ans);
		if(R > mid) qry(L, R, mid + 1, r, rs, ans);
	}
}seg;
// id starts with 1
struct HeavyChain{
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
		if(s) top[s] = top[c], dfs2(s, c, g), leaf[c] = leaf[s];
		else leaf[c] = c;
		for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c, g);
	}
	void Build(vi g[]){
		dfs(1, 0, g);
		_=0;
		dfs2(1, 0, g);
	}
}hc;
inline pair<ll, ll> qry(int x) {
	Mat tmp; seg.qry(id[x], id[leaf[x]], 1, n, 1, tmp);
	ll f0 = min(tmp.a[0][0], tmp.a[0][1]);
	ll f1 = min(tmp.a[1][0], tmp.a[1][1]);
	return mp(f0, f1);
}
void upd(int u, int o, ll val) {
	F[u][o] = val;
	int v = u;
	while(v) {
		int u = top[v], fa = par[u];
		seg.upd(v, 1, n, 1);
		pair<ll, ll> _f = qry(u);
		if(fa) {
			F[fa][0] += _f.se - f[u][1];
			F[fa][1] += min(_f.fi, _f.se) - min(f[u][0], f[u][1]);
		}
		f[u][0] = _f.fi, f[u][1] = _f.se, v = fa;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> op;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	hc.Build(g);
	seg.build(1, n, 1);
	while(m--) {
		int u, x, v, y;
		cin >> u >> x >> v >> y;
		ll fu = F[u][x ^ 1], fv = F[v][y ^ 1];
		upd(u, x ^ 1, inf);
		upd(v, y ^ 1, inf);
		pair<ll, ll> tmp = qry(1);
		ll ans = min(tmp.fi, tmp.se);
		if(ans >= inf) ans = -1;
		cout << ans << endl;
		upd(u, x ^ 1, fu);
		upd(v, y ^ 1, fv);
	}
	return 0;
}
