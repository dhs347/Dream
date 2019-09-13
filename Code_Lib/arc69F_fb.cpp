#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a < 0 ? a + P : a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
int kpow(int a, int b) {
	int r=1;
	for(; b; b>>=1,a=mul(a,a)) {
		if(b&1)r=mul(r,a);
	}
	return r;
}
//----

const int N = 5e5 + 7;

struct TwoSat {
	static const int N = ::N << 1;
	int dfn[N], low[N], id[N], st[N], _st, _, cc;
	vi g[N];
	int mark[N], n;
	void init(int _n) {
		per(i, 0, (n = _n << 1)) g[i].clear();
	}
	int  new_node( ) {
		rep(i, 0, 2) g[n++].clear();
		return n >> 1;
	}
	/// optionals begin
	void addedge(int a, int va, int b, int vb) { // va 选了 vb 必选
		a = a << 1 | va;
		b = b << 1 | vb;
		g[a].pb(b);
		g[b ^ 1].pb(a ^ 1);
	}
	void add_set(int a, int va) {
		a = a << 1 | va;    // va 必选
		g[a ^ 1].pb(a);
	}

	void add_then(int a, int va, int b, int vb) { // va 和 vb 不能同时取
		addedge(a, va, b, vb ^ 1);
	}
	void add_or (int a, int va, int b, int vb) { // va 和 vb 不能同时不取
		addedge(a, va ^ 1, b, vb);
	}
	void add_xor(int a, int va, int b, int vb) { // va 和 vb 同时取或同时不取
		addedge(a, va, b, vb);
		addedge(b, vb, a, va);
	}
	// 需要 sz(vu) 个额外的 dp 变量
	void add_at_most_one(vector<pii> vu) {
		int pre = -1;
		rep(i, 0, sz(vu)) {
			int a = vu[i].fi, va = vu[i].se;
			int dpi = new_node();
			add_then(a, va, dpi, 1);
			if (i) {
				add_then(pre, 1, dpi, 1);
				add_then(pre, 1, a, va ^ 1);
			}
			pre = dpi;
		}
	}
	// optionals end

	void dfs(int c, vi g[]) {
		dfn[c] = low[c] = ++cc;
		st[_st++] = c;
		//for(auto t : g[c])
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(!dfn[t])
				dfs(t, g), low[c] = min(low[c], low[t]);
			else if(!id[t])
				low[c] = min(low[c], dfn[t]);
		}
		if(low[c] == dfn[c]) {
			++_;
			do {
				id[st[--_st]]=_;
			} while(st[_st] != c);
		}
	}
	void find(vi g[]) {
		fill_n(dfn, n, cc=0);
		fill_n(low, n, _st=0);
		fill_n(id, n, _=0);
		rep(i, 0, n) if(!dfn[i]) dfs(i, g);
		rep(i, 0, n) --id[i];
		return;
	}
	bool solve() { // 构造任意解
		find(g);
		for (int i = 0; i < n; i += 2) {
			if (id[i] == id[i + 1]) return 0;
			mark[i >> 1] = (id[i] > id[i + 1]);
		}
		return 1;
	}
}  ts;

vector<pair<int, pii> > vx;
int n, pos[N][2], x[N], y[N];
struct SegGraph {
#define ls (rt << 1)
#define rs (ls | 1)
	int id[N][2], tim, p[N];
	vector<int> g[N];
	void init() {
		rep(i, 0, tim) g[i].clear();
		tim = 0;
	}
	void liu(int u, int v, int w) {
		g[u].pb(v);
	}

	void build(int l, int r, int rt) {
		int *t = id[rt], *fa = id[rt / 2], mid = l + r >> 1;
		t[0] = ++tim;
		t[1] = ++tim;
		liu(t[0], t[1], 0);
		if (rt / 2) liu(fa[0], t[0], 0), liu(t[1], fa[1], 0);
		if (l == r) {
			p[l] = t[0];
			return;
		}
		build(l, mid, ls);
		build(mid+1, r, rs);
	}

	void link(int l, int r, int rt, int L, int R, int w, int o) {
		int *t = id[rt], mid = l + r >> 1;
		if (L <= l && R >= r) {
			if (o) liu(t[o], tim, w);
			else liu(tim, t[o], w);
			return;
		}
		if (L <= mid) link(l, mid, ls, L, R, w, o);
		if (R > mid)  link(mid+1, r, rs, L, R, w, o);
	}

	void link(int l1, int r1, int l2, int r2, int w, int n) {
		++tim;
		link(1, n, 1, l1, r1, w, 0);
		link(1, n, 1, l2, r2, w, 1);
	}

} G;

bool check(int mid) {
	G.init();
	G.build(1, n*2, 1);
	rep(i, 0, n * 2) {
		int l = lower_bound(all(vx), mp(vx[i].fi - mid + 1, mp(-1, -1))) - vx.begin();
		int r = upper_bound(all(vx), mp(vx[i].fi + mid - 1, mp((int)pw(30), 0))) - vx.begin();
		int u = pos[vx[i].se.fi][vx[i].se.se];
		if (l + 1 <= i) G.link(u, u, l + 1, i, 0, n * 2);
		if (i + 2 <= r) G.link(u, u, i + 2, r, 0, n * 2);
	}
	ts.n = G.tim + 1;
	ts.find(G.g);
	rep(i, 0, ts.n) ts.g[i].clear();
	rep(i, 0, n) {
		if (ts.id[G.p[pos[i][0]]] == ts.id[G.p[pos[i][1]]]) return 0;
	}
	return 1;
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 0, n) {
		cin >> x[i] >> y[i];
		vx.pb(mp(x[i], mp(i, 0)));
		vx.pb(mp(y[i], mp(i, 1)));
	}
	sort(all(vx));
	rep(i, 0, n * 2) pos[vx[i].se.fi][vx[i].se.se ^ 1] = i + 1;
	int l = 0, r = 1e9, ans = 0;
	while (l <= r) {
		int mid = l + r >> 1;
		if (check(mid)) ans = mid, l = mid + 1;
		else r = mid - 1;
	}
	cout << ans << endl;
	return 0;
}


