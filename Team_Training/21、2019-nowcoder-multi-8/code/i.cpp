#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 303030;

int n, m, q, L;
int l[N], r[N], st[N], ed[N];
vi g[N], vec[N], vv[N];
int Q[N];
ll ans[N];
int C; ll S, T;
int now;

void dfs(int u) {
	st[u] = ++L;
	for(auto v : g[u]) dfs(v);
	ed[u] = L;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int cnt[N];
	ll sum[N], tot[N];
	void up(int rt) {
		cnt[rt] = cnt[ls] + cnt[rs];
		sum[rt] = sum[ls] + sum[rs];
		tot[rt] = tot[ls] + tot[rs];
	}
	void upd(int p, int c, int l, int r, int rt) {
		if(l == r) {
			if(c == 0) tot[rt] += now - sum[rt];
			sum[rt] = c;
			cnt[rt] = (c > 0);
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, l, mid, ls);
		else upd(p, c, mid + 1, r, rs);
		up(rt);
	}
	void qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			S += sum[rt];
			C += cnt[rt];
			T += tot[rt];
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) qry(L, R, l, mid, ls);
		if(R > mid) qry(L, R, mid + 1, r, rs);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		cin >> l[v] >> r[v];
		g[u].pb(v);
		vv[l[v]].pb(v);
		vv[r[v] + 1].pb(-v);
	}
	vv[1].pb(1);
	dfs(1);
	cin >> q;
	rep(i, 1, q + 1) {
		int l, r; cin >> Q[i] >> l >> r;
		vec[l - 1].pb(-i);
		vec[r].pb(i);
	}
	rep(i, 1, n + 1) {
		now = i;
		for(auto u : vv[i]) {
			//dd(i), dd(u);
			if(u > 0) {
				seg.upd(st[u], i, 1, m + 1, 1);
			} else {
				seg.upd(st[-u], 0, 1, m + 1, 1);
			}
		//	dd(seg.cnt[1]), dd(seg.sum[1]), de(seg.tot[1]);
		}
		for(auto ind : vec[i]) {
			int o = ind / abs(ind);
			int u = Q[abs(ind)];
			C = S = T = 0;
			seg.qry(st[u], ed[u], 1, m + 1, 1);
			//dd(ind), dd(C), dd(S), de(T);
			ans[abs(ind)] += o * ((i + 1) * 1ll * C - S + T);
		}
	}
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
