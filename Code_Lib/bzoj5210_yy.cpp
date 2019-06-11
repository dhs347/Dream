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

int n, m;
int a[N];
int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N], leaf[N];
ll f[N][2], F[N][2];
vi g[N];

struct Heap {
	priority_queue<ll> q1, q2;
	inline void ins(ll x) {
		q1.push(x);
	}
	inline void del(ll x) {
		q2.push(x);
	}
	inline void top(ll &x) {
		while(!q1.empty()) {
			ll t = q1.top();
			if(!q2.empty() && t == q2.top()) {
				q1.pop(); q2.pop();
			} else {
				x = t;
				return ;
			}
		}
		x = -inf;
	}
}que[N];

inline ll max(ll a, ll b) {
	return a < b ? b : a;
}
inline ll max(ll a, ll b, ll c) {
	if(a > b && a > c) return a;
	return b < c ? c : b;
}

struct Mat {
	ll a[3][3];
	inline Mat operator * (const Mat &c) const {
		Mat r;
		r.a[0][0] = max(a[0][0] + c.a[0][0], a[0][1] + c.a[1][0], a[0][2] + c.a[2][0]);
		r.a[0][1] = max(a[0][0] + c.a[0][1], a[0][1] + c.a[1][1], a[0][2] + c.a[2][1]);
		r.a[0][2] = max(a[0][0] + c.a[0][2], a[0][1] + c.a[1][2], a[0][2] + c.a[2][2]);
		r.a[1][0] = max(a[1][0] + c.a[0][0], a[1][1] + c.a[1][0], a[1][2] + c.a[2][0]);
		r.a[1][1] = max(a[1][0] + c.a[0][1], a[1][1] + c.a[1][1], a[1][2] + c.a[2][1]);
		r.a[1][2] = max(a[1][0] + c.a[0][2], a[1][1] + c.a[1][2], a[1][2] + c.a[2][2]);
		r.a[2][0] = max(a[2][0] + c.a[0][0], a[2][1] + c.a[1][0], a[2][2] + c.a[2][0]);
		r.a[2][1] = max(a[2][0] + c.a[0][1], a[2][1] + c.a[1][1], a[2][2] + c.a[2][1]);
		r.a[2][2] = max(a[2][0] + c.a[0][2], a[2][1] + c.a[1][2], a[2][2] + c.a[2][2]);
		return r;
	}
	inline void e() {
		rep(i, 0, 3) {
			rep(j, 0, 3) a[i][j] = (i != j) * (-inf);
		}
	}
};

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	Mat m[N];
	inline void build(int l, int r, int rt) {
		if(l == r) {
			int u = who[l], s = wson[u];
			F[u][1] = a[u];
			rep(i, 0, sz(g[u])) {
				int v = g[u][i];
				if(v != par[u] && v != s) {
					que[u].ins(f[v][0]);
					que[u].ins(f[v][1]);
					F[u][1] += max(0ll, f[v][1]);
				}
			}
			que[u].top(F[u][0]);
			f[u][0] = max(F[u][0], f[s][0], f[s][1]);
			f[u][1] = max(0ll, f[s][1]) + F[u][1];
			m[rt].a[0][2] = F[u][0];
			m[rt].a[1][1] = m[rt].a[1][2] = F[u][1];
			m[rt].a[1][0] = m[rt].a[2][0] = m[rt].a[2][1] = -inf;
			return ;
		}
		int mid = l + r >> 1;
		build(mid + 1, r, rs);
		build(l, mid, ls);
		m[rt] = m[ls] * m[rs];
	}
	inline void upd(int u, int l, int r, int rt) {
		if(l == r) {
			m[rt].a[0][2] = F[u][0];
			m[rt].a[1][1] = m[rt].a[1][2] = F[u][1];
			return ;
		}
		int mid = l + r >> 1;
		if(id[u] <= mid) upd(u, l, mid, ls);
		else upd(u, mid + 1, r, rs);
		m[rt] = m[ls] * m[rs];
	}
	inline void qry(int L, int R, int l, int r, int rt, Mat &ans) {
		if(L <= l && r <= R) return ans = ans * m[rt], void();
		int mid = l + r >> 1;
		if(L <= mid) qry(L, R, l, mid, ls, ans);
		if(R > mid) qry(L, R, mid + 1, r, rs, ans);
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

inline pair<ll, ll> qry(int x) {
	Mat tmp; tmp.e(); seg.qry(id[x], id[leaf[x]], 1, n, 1, tmp);
	ll f0 = max(tmp.a[0][0], tmp.a[0][1], tmp.a[0][2]);
	ll f1 = max(tmp.a[1][0], tmp.a[1][1], tmp.a[1][2]);
	return mp(f0, f1);
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
		string o;
		cin >> o;
		if(o[0] == 'Q') {
			int x; cin >> x;
			pair<ll, ll> ans = qry(x);
			cout << max(ans.fi, ans.se) << endl;
		} else {
			int p, c;
			cin >> p >> c;
			F[p][1] += c - a[p];
			a[p] = c;
			int v = p;
			while(v) {
				int u = top[v], fa = par[u];
				seg.upd(v, 1, n, 1);
				pair<ll, ll> _f = qry(u);
				if(fa) {
					que[fa].del(f[u][0]);
					que[fa].del(f[u][1]);
					que[fa].ins(_f.fi);
					que[fa].ins(_f.se);
					que[fa].top(F[fa][0]);
					F[fa][1] += max(0ll, _f.se) - max(0ll, f[u][1]);
				}
				f[u][0] = _f.fi;
				f[u][1] = _f.se;
				v = fa;
			}
		}
	}
	return 0;
}
