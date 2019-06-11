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
typedef ll T;

const int N = 101010;
const T inf = 1e18;

int n, m;
int a[N], par[N], wson[N], who[N], top[N], id[N], leaf[N];
T f[N][2], F[N][2];
vi g[N];

struct Mat {
	T a[2][2];
	Mat operator * (const Mat &c) const {
		Mat r;
		rep(i, 0, 2) rep(j, 0, 2) {
			r.a[i][j] = max(a[i][0] + c.a[0][j], a[i][1] + c.a[1][j]);
		}
		return r;
	}
	void e() {
		a[0][0] = a[1][1] = 0;
		a[0][1] = a[1][0] = -inf;
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
			F[u][1] = a[u];
			for(auto v : g[u]) if(v != par[u] && v != s) {
				F[u][0] += max(f[v][0], f[v][1]);
				F[u][1] += f[v][0];
			}
			f[u][0] = max(f[s][0], f[s][1]) + F[u][0];
			f[u][1] = f[s][0] + F[u][1];
			m[rt].a[0][0] = m[rt].a[0][1] = F[u][0];
			m[rt].a[1][0] = F[u][1];
			m[rt].a[1][1] = -inf;
			return ;
		}
		int mid = l + r >> 1;
		build(mid + 1, r, rs);
		build(l, mid, ls);
		up(rt);
	}
	void upd(int u, int l, int r, int rt) {
		if(l == r) {
			m[rt].a[0][0] = m[rt].a[0][1] = F[u][0];
			m[rt].a[1][0] = F[u][1];
			m[rt].a[1][1] = -inf;
			return ;
		}
		int mid = l + r >> 1;
		if(id[u] <= mid) upd(u, l, mid, ls);
		else upd(u, mid + 1, r, rs);
		up(rt);
	}
	Mat qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return m[rt];
		int mid = l + r >> 1;
		Mat ans; ans.e();
		if(L <= mid) ans = ans * qry(L, R, l, mid, ls);
		if(R > mid) ans = ans * qry(L, R, mid + 1, r, rs);
		return ans;
	}
}seg;

// id starts with 1
struct HeavyChain{
	static const int N = ::N;
	int sz[N], dep[N], _;
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

pair<T, T> qry(int s) {
	if(!s) return mp(0, 0);
	Mat ans = seg.qry(id[s], id[leaf[s]], 1, n, 1);
	return mp(max(ans.a[0][0], ans.a[0][1]), max(ans.a[1][0], ans.a[1][1]));
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
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
		int x, y;
		cin >> x >> y;
		int u = x;
		F[x][1] += y - a[x], a[x] = y;
		while(u) {
			seg.upd(u, 1, n, 1);
			int fa = top[u];
			Mat tmp = seg.qry(id[fa], id[u], 1, n, 1);
			int s = wson[u];
			auto fs = qry(s);
			T f0 = max(tmp.a[0][0] + fs.fi, tmp.a[0][1] + fs.se);
			T f1 = max(tmp.a[1][0] + fs.fi, tmp.a[1][1] + fs.se);
			int ff = par[fa];
			if(ff) {
				F[ff][0] += max(f0, f1) - max(f[fa][0], f[fa][1]);
				F[ff][1] += f0 - f[fa][0];
			}
			f[fa][0] = f0;
			f[fa][1] = f1;
			u = ff;
		}
		auto ans = qry(1);
		cout << max(ans.fi, ans.se) << endl;
	}
	return 0;
}
