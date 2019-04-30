#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
#define ls rt << 1
#define rs ls | 1
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 101010;

int n;
int col[N], cnt[N];
vi g[N];
ll ans[N];

int sz[N], wson[N], par[N];

struct Seg {
	static const int N = ::N << 2;
	ll sum[N];
	void upd(int p, ll c, int l, int r, int rt) {
		if(p == 0) return ;
		sum[rt] += c;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
	}
	ll qry(int l, int r, int rt) {
		if(l == r) return sum[rt];
		int mid = l + r >> 1;
		if(sum[rs]) return qry(mid + 1, r, rs);
		return qry(l, mid, ls);
	}
}seg;

void dfs(int c, int fa) {
	sz[c] = 1, par[c] = fa;
	int &s = wson[c] = 0;
	for(auto t : g[c]) if(t != fa) {
		dfs(t, c);
		sz[c] += sz[t];
		(sz[t] >= sz[s]) && (s = t);
	}
}
void upd(int p, int c) {
	seg.upd(cnt[p], -p, 1, n, 1);
	cnt[p] += c;
	seg.upd(cnt[p], p, 1, n, 1);
}
vi nd;
void dfs2(int u, int fa) {
	nd.pb(u);
	upd(col[u], 1);
	for(auto v : g[u]) if(v != fa) {
		dfs2(v, u);
	}
}
void solve(int c, int fa, bool iswson) {
	for(auto t : g[c]) if(t != wson[c] && t != fa) solve(t, c, 0);
	if(wson[c]) solve(wson[c], c, 1);
	for(auto t : g[c]) if(t != wson[c] && t != fa) {
		dfs2(t, c);
	}
	nd.pb(c);
	upd(col[c], 1);
	ans[c] = seg.qry(1, n, 1);
	if(!iswson) {
		for(auto u : nd) upd(col[u], -1);
		nd.clear();
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> col[i];
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	solve(1, 0, 1);
	rep(i, 1, n + 1) cout << ans[i] << " \n"[i == n];
	return 0;
}
