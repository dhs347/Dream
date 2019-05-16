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

const int N = 50505, P = 201314;

int n, q;
ll ans[N];
vi g[N];
vector<pii> Q[N];

int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int sub(int a, int b) {
	if((a -= b) < 0) a += P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int sum[N], la[N];
	void gao(int rt, int l, int r, int c) {
		sum[rt] = add(sum[rt], mul(r - l + 1, c));
		la[rt] = add(la[rt], c);
	}
	void down(int rt, int l, int r, int mid) {
		if(la[rt]) gao(ls, l, mid, la[rt]), gao(rs, mid + 1, r, la[rt]), la[rt] = 0;
	}
	void up(int rt) {
		sum[rt] = add(sum[ls], sum[rs]);
	}
	void upd(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			gao(rt, l, r, 1);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, l, mid, ls);
		if(R > mid) upd(L, R, mid + 1, r, rs);
		up(rt);
	}
	int qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return sum[rt];
		int mid = l + r >> 1;
		down(rt, l, r, mid); 
		int ans = 0;
		if(L <= mid) ans = add(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = add(ans, qry(L, R, mid + 1, r, rs));
		up(rt);
		return ans;
	}
}seg;

// id starts with 1
struct HeavyChain{
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N];
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
	void upd(int a, int b) {
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			seg.upd(id[fa], id[a], 1, n, 1);
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		seg.upd(id[b], id[a], 1, n, 1);
	}
	ll qry(int a, int b) {
		ll ans = 0;
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			ans = add(ans, seg.qry(id[fa], id[a], 1, n, 1));
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		ans = add(ans, seg.qry(id[b], id[a], 1, n, 1));
		return ans;
	}
	void Query(int a, int b){
		int fa = top[a], fb = top[b];
		while(fa != fb){
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			// Cal id[fa] .. id[a]
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		// Cal id[b] .. id[a]
		// b is lca
	}
	void Build(vi g[]){
		dfs(1, 0, g);
		_=0;
		dfs2(1, 0, g);
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> q;
	rep(i, 2, n + 1) {
		int u; cin >> u; ++u;
		g[u].pb(i);
	}
	hc.Build(g);
	rep(i, 1, q + 1) {
		int l, r, z; 
		cin >> l >> r >> z;
		++l, ++r, ++z;
		if(l > 1) Q[l - 1].pb(mp(z, -i));
		Q[r].pb(mp(z, i));
	}
	rep(i, 1, n + 1) {
		hc.upd(1, i);
		rep(j, 0, sz(Q[i])) {
			pii t = Q[i][j];
			ll res = hc.qry(1, t.fi);
			if(t.se > 0) ans[t.se] = add(ans[t.se], res);
			else ans[-t.se] = sub(ans[-t.se], res);
		}
	}
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
