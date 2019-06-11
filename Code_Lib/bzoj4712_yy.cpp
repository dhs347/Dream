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
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202020;
const ll inf = 1e18;

int n;
int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N], leaf[N];
ll a[N], f[N], F[N];
vi g[N];

struct Mat {
	ll a[2][2];
	Mat operator * (const Mat &c) const {
		Mat r;
		rep(i, 0, 2) rep(j, 0, 2) {
			r.a[i][j] = min(a[i][0] + c.a[0][j], a[i][1] + c.a[1][j]);
		}
		return r;
	}
	void e() {
		a[0][0] = a[1][1] = 0;
		a[0][1] = a[1][0] = inf;
	}
	void print() {
		rep(i, 0, 2) rep(j, 0, 2) dd(i), dd(j), de(a[i][j]);
	}
};

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	Mat m[N];
	void up(int rt) {
		m[rt] = m[ls] * m[rs];
	}
	void build(int l, int r, int rt) {
		if(l == r) {
			int u = who[l], s = wson[u];
			rep(i, 0, sz(g[u])) {
				int v = g[u][i];
				if(v != par[u] && v != s) F[u] += f[v];
			}
			if(!s) F[u] = inf;
			f[u] = min(F[u] + f[s], a[u]);
			m[rt].a[0][0] = F[u];
			m[rt].a[0][1] = a[u];
			return ;
		}
		int mid = l + r >> 1;
		build(mid + 1, r, rs);
		build(l, mid, ls);
		up(rt);
	}
	void upd(int u, int l, int r, int rt) {
		if(l == r) {
			m[rt].a[0][0] = F[u];
			m[rt].a[0][1] = a[u];
			return ;
		}
		int mid = l + r >> 1;
		if(id[u] <= mid) upd(u, l, mid, ls);
		else upd(u, mid + 1, r, rs);
		up(rt);
	}
	Mat qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return m[rt];
		Mat ans; ans.e();
		int mid = l + r >> 1;
		if(L <= mid) ans = ans * qry(L, R, l, mid, ls);
		if(R > mid) ans = ans * qry(L, R, mid + 1, r, rs);
		return ans;
	}
}seg;

// id starts with 1
struct HeavyChain{
	static const int N = ::N;
	void dfs(int c, int fa, vi g[]){
		sz[c] = 1;
		par[c] = fa;
		dep[c] = dep[fa] + 1;
		int &s = wson[c] = top[c] = 0;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t == fa) continue;
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
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t != fa && t != s) dfs2(t, c, g);
		}
	}
	void Build(vi g[]){
		dfs(1, 0, g);
		_=0;
		dfs2(1, 0, g);
	}
}hc;

ll qry(int x) {
	Mat tmp = seg.qry(id[x], id[leaf[x]], 1, n, 1);
	return min(tmp.a[0][0], tmp.a[0][1]);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	hc.Build(g);
	seg.build(1, n, 1);
	int m;
	cin >> m;
	while(m--) {
		string o;
		cin >> o;
		if(o[0] == 'Q') {
			int x; cin >> x;
			cout << qry(x) << endl;
		} else {
			int p; ll c; cin >> p >> c;
			a[p] += c;
			int v = p;
			while(v) {
				seg.upd(v, 1, n, 1);
				int u = top[v], s = wson[v], fa = par[u];
				ll _f = qry(u);
				if(fa) F[fa] += _f - f[u];
				f[u] = _f;
				v = fa;
			}
		}
	}
	return 0;
}
