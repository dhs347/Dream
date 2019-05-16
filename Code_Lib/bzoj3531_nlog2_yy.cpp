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

const int N = 101010;

int n, m;
int a[N], b[N], who[N], id[N];
vi g[N];

struct Seg {
	static const int N = ::N * 100;
	int cntL;
	int ls[N], rs[N], ma[N], rt[N];
	ll sum[N];
	void up(int rt) {
		ma[rt] = max(ma[ls[rt]], ma[rs[rt]]);
		sum[rt] = sum[ls[rt]] + sum[rs[rt]];
	}
	void upd(int p, int c, int &rt, int l, int r) {
		if(!rt) rt = ++cntL;
		if(l == r) {
			ma[rt] = sum[rt] = c;
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, c, ls[rt], l, mid);
		else upd(p, c, rs[rt], mid + 1, r);
		up(rt);
	}
	pair<ll, int> qry(int L, int R, int rt, int l, int r) {
		if(!rt) return mp(0, 0);
		if(L <= l && r <= R) return mp(sum[rt], ma[rt]);
		int mid = l + r >> 1, Ma = 0;
		ll Sum = 0;
		if(L <= mid) {
			pair<ll, int> t = qry(L, R, ls[rt], l, mid);
			Sum += t.fi;
			Ma = max(Ma, t.se);
		}
		if(R > mid) {
			pair<ll, int> t = qry(L, R, rs[rt], mid + 1, r);
			Sum += t.fi;
			Ma = max(Ma, t.se);
		}
		return mp(Sum, Ma);
	}
}seg;

// id starts with 1
struct HeavyChain{
	static const int N = ::N;
	int sz[N], wson[N], top[N], dep[N], _, par[N];
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
	pair<ll, int> qry(int a, int b) {
		int A = ::a[a];
		int fa = top[a], fb = top[b];
		ll sum = 0; int ma = 0;
		while(fa != fb) {
			if(dep[fa] < dep[fb]) swap(a, b), swap(fa, fb);
			pair<ll, int> t = seg.qry(id[fa], id[a], seg.rt[A], 1, n); 
			sum += t.fi; ma = max(ma, t.se);
			a = par[fa]; fa = top[a];
		}
		if(dep[a] < dep[b]) swap(a, b);
		pair<ll, int> t = seg.qry(id[b], id[a], seg.rt[A], 1, n);
		sum += t.fi; ma = max(ma, t.se);
		return mp(sum, ma);
	}
	void build(vi g[]){
		dfs(1, 0, g);
		_=0;
		dfs2(1, 0, g);
		rep(i, 1, n + 1) seg.upd(id[i], b[i], seg.rt[a[i]], 1, n);
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	db tt = sizeof(seg);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> b[i] >> a[i];
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	hc.build(g);
	while(m--) {
		string s; int x, y;
		cin >> s >> x >> y;
		if(s[0] == 'C') {
			seg.upd(id[x], 0, seg.rt[a[x]], 1, n);
			(s[1] == 'C') ? a[x] = y : b[x] = y;
			seg.upd(id[x], b[x], seg.rt[a[x]], 1, n);
		} else {
			pair<ll, int> ans = hc.qry(x, y);
			cout << (s[1] == 'S' ? ans.fi : ans.se) << endl;
		}
	}
	return 0;
}
