#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 10101, P = 1e9 + 7;

int n, dfn, st[N], ed[N], dis[N], ddf[N];
ll ans[3];
vector<pii> g[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll sum[3][N], la[N]; int cnt[3][N];
	void up(int rt) {
		rep(o, 0, 3) {
			sum[o][rt] = sum[o][ls] + sum[o][rs];
			cnt[o][rt] = cnt[o][ls] + cnt[o][rs];
		}
	}
	void build(int l = 1, int r = n, int rt = 1) {
		rep(o, 0, 3) sum[o][rt] = cnt[o][rt] = 0; la[rt] = 0;
		if(l == r) {
			int k = ddf[l];
			int o = dis[k] % 3;
			sum[o][rt] += dis[k];
			cnt[o][rt]++;
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void gao(int rt, ll c) {
		la[rt] += c;
		rep(o, 0, 3) sum[o][rt] += cnt[o][rt] * c;
		int o = (c % 3 + 3) % 3;
		if(o == 1) {
			auto t = sum[2][rt];
			sum[2][rt] = sum[1][rt];
			sum[1][rt] = sum[0][rt];
			sum[0][rt] = t;
			t = cnt[2][rt];
			cnt[2][rt] = cnt[1][rt];
			cnt[1][rt] = cnt[0][rt];
			cnt[0][rt] = t;
		} else if(o == 2) {
			auto t = sum[0][rt];
			sum[0][rt] = sum[1][rt];
			sum[1][rt] = sum[2][rt];
			sum[2][rt] = t;
			t = cnt[0][rt];
			cnt[0][rt] = cnt[1][rt];
			cnt[1][rt] = cnt[2][rt];
			cnt[2][rt] = t;
		}
	}
	void down(int rt) {
		if(la[rt]) {
			gao(ls, la[rt]);
			gao(rs, la[rt]);
			la[rt] = 0;
		}
	}
	void upd(int L, int R, ll c, int l = 1, int r = n, int rt = 1) {
//		if(rt == 1) dd(L), dd(R), de(c);
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
}seg;

void dfs(int u, int fa) {
	st[u] = ++dfn;
	ddf[dfn] = u;
	for(auto v : g[u]) if(v.fi != fa) {
		dis[v.fi] = dis[u] + v.se;
		dfs(v.fi, u);
	}
	ed[u] = dfn;
}

void solve(int u, int fa) {
	rep(o, 0, 3) ans[o] += seg.sum[o][1];//, dd(seg.sum[o][1]); cout << endl;
	for(auto v : g[u]) if(v.fi != fa) {
		seg.upd(1, n, v.se);
		seg.upd(st[v.fi], ed[v.fi], -2ll * v.se);
		solve(v.fi, u);
		seg.upd(1, n, -v.se);
		seg.upd(st[v.fi], ed[v.fi], 2ll * v.se);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n) {
		rep(i, 1, n + 1) g[i].clear();
		dfn = 0;
		rep(i, 1, n) {
			int u, v, w; cin >> u >> v >> w;
			++u, ++v;
			g[u].pb(mp(v, w));
			g[v].pb(mp(u, w));
		}
		dfs(1, 0);
		seg.build();
		rep(o, 0, 3) ans[o] = 0;
		solve(1, 0);
		rep(o, 0, 3) cout << ans[o] % P << " \n"[o == 2];
		/*
		rep(i, 1, n + 1) {
			dis[i] = 0;
			dfs(i, 0);
			seg.build();
			dd(i);
			rep(o, 0, 3) dd(seg.sum[o][1]); cout << endl;
		}*/
	}
	return 0;
}
