#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;

int n, C, q;
int cnt[N], num[N];
vi g[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int col[N], la[N];
	void down(int rt) {
		if(!la[rt]) return ;
		col[ls] = col[rs] = la[ls] = la[rs] = la[rt];
		la[rt] = 0;
	}
	void up(int rt) {
		if(col[ls] == col[rs] && col[ls] != -1) col[rt] = col[ls];
		else col[rt] = -1;
	}
	void upd(int L, int R, int c, int l, int r, int rt) {
		if(rt == 1) {
			if(L == 1) ++L;
			if(L > R) return ;
		}
		if(L <= l && r <= R && col[rt] != -1) {

			--num[cnt[col[rt]]];
			cnt[col[rt]] -= r - l + 1;
			++num[cnt[col[rt]]];

			col[rt] = la[rt] = c;

			--num[cnt[col[rt]]];
			cnt[col[rt]] += r - l + 1;
			++num[cnt[col[rt]]];
			return ;
		}
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
}seg;

struct HC {
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N];
	void dfs(int c, int fa, vi g[]) {
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
	void dfs2(int c, int fa, vi g[]) {
		id[c] = ++_;
		who[_] = c;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c, g);
		for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c, g);
	}
	void build(vi g[]) {
		dfs(1, 0, g); _ = 0; dfs2(1, 0, g);
	}
	void upd(int a, int c) {
		int b = 1;
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			seg.upd(id[fa], id[a], c, 2, n, 1);
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		seg.upd(id[b], id[a], c, 2, n, 1);
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> C >> q;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v); g[v].pb(u);
	}
	cnt[0] = n - 1; num[n - 1] = 1;
	rep(i, 1, C + 1) cnt[i] = 0; num[0] += C;
	hc.build(g);
	while(q--) {
		int u, c, m;
		cin >> u >> c >> m;
		hc.upd(u, c);
		cout << (num[m] - (cnt[0] == m)) << endl;
	}
	return 0;
}
