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

const int N = 2500 + 7, P = 998244353;

int n, m, q;
int a[N];
vector<pair<int, string> > G[N];
vi g[N];

inline int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
inline int mul(int a, int b) {
	return 1ll * a * b % P;
}


struct AC {
	static const int N = 44, M = 26;
	int ne[N][M], fail[N], fa[N], rt, L, ed[N];
	void init() { rt = L++; }
	void add(char *s) {
		int p = rt;
		for(int i = 0; s[i]; ++i) {
			int c = s[i] - 'a';
			if(!ne[p][c]) ne[p][c] = L++, fa[L - 1] = p;
			p = ne[p][c];
		}
		ed[p] = 1;
	}
	void build() {
		vi v; v.pb(rt);
		rep(i, 0, sz(v)) {
			int c = v[i];
			rep(i, 0, M) ne[c][i] ? 
			v.pb(ne[c][i]), fail[ne[c][i]] = ne[fail[c]][i] : 
			ne[c][i] = ne[fail[c]][i];
		}
	}
}ac;



struct Mat {
	static const int N = 44;
	int n;
	int a[N][N];
	Mat() { n = ac.L;  rep(i, 0, N) rep(j, 0, N) a[i][j] = 0; }
	void set() {
		rep(i, 0, n) a[i][i] = 1;
	}
	Mat(int n) : n(n) {
	
		rep(i, 0, N) rep(j, 0, N) a[i][j] = 0; }
	Mat operator * (const Mat &c) const {
		Mat r = Mat(ac.L);
		rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
		return r;
	}
}mat[N], premat[N];



struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	Mat nd[N], dn[N]; int cnt[N];
	void build(int l, int r, int rt) {
		if(l == r) {
			nd[rt] = dn[rt] = mat[l];
			cnt[rt] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		nd[rt] = nd[ls] * nd[rs];
		dn[rt] = dn[rs] * dn[ls];
		cnt[rt] = mul(cnt[ls], cnt[rs]);
	}
	int qry3(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return cnt[rt];
		int mid = l + r >> 1, ans = 1;
		if(L <= mid) ans = mul(ans, qry3(L, R, l, mid, ls));
		if(R > mid) ans = mul(ans, qry3(L, R, mid + 1, r, rs));
		return ans;
	}
	Mat qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return nd[rt];
		int mid = l + r >> 1;
		Mat ans = Mat(ac.L); ans.set();
		if(L <= mid) ans = ans * qry(L, R, l, mid, ls);
		if(R > mid) ans = ans * qry(L, R, mid + 1, r, rs);
		return ans;
	}
	Mat qry2(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return dn[rt];
		int mid = l + r >> 1;
		Mat ans = Mat(ac.L); ans.set();
		if(R > mid) ans = ans * qry2(L, R, mid + 1, r, rs);
		if(L <= mid) ans = ans * qry2(L, R, l, mid, ls);
		return ans;
	}
} seg;

struct HC {
	static const int N = 2500 + 5;
	int sz[N], wson[N], top[N], dep[N], id[N], _, par[N], who[N];
	void dfs(int c, int fa) {
		sz[c] = 1;
		par[c] = fa;
		dep[c] = dep[fa] + 1;
		int &s = wson[c] = top[c] = 0;
		for(auto k : G[c]) if(k.fi != fa) {
			int t = k.fi;
			dfs(t, c);
			sz[c] += sz[t];
			if(sz[t] >= sz[s]) s = t;
		}
	}

	void dfs3(int c, int fa) {
		for(auto k : G[c]) if(k.fi != fa) {
			int t = k.fi;
			int idt = id[t];
			a[idt] = sz(k.se);
			mat[idt] = Mat(ac.L);
			rep(i, 0, ac.L) if (!ac.ed[i]){
				for (auto u : k.se) {
					int t = ac.ne[i][u - 'a'];
					if (!ac.ed[t]) {
						mat[idt].a[i][t]++;
					}
				}
			}
			dfs3(t, c);
		}
	}
	void dfs2(int c, int fa) {
		id[c] = ++_;
		who[_] = c;
		int s = wson[c];
		if(!top[c]) top[c] = c;
		if(s) top[s] = top[c], dfs2(s, c);
		for(auto t : g[c]) if(t != fa && t != s) dfs2(t, c);
	}

	void qry(int a, int b) {
		vector<pii> tmp[2];
		int o = 1;
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			if(dep[fa] < dep[fb]) o ^= 1, swap(a, b), swap(fa, fb);
			tmp[o].pb(mp(id[fa], id[a]));
			a = par[fa], fa = top[a];
		}
		if(dep[a] < dep[b]) o ^= 1, swap(a, b);
		if (dep[a] != dep[b]) tmp[o].pb(mp(id[b]+1, id[a]));
		Mat ans = Mat(ac.L);
		//ans.a[0][0] = 1;
		ans.set();
		ll an = 1;
		per(i, 0, sz(tmp[0])) {
			dd(tmp[0][i].fi);
			de(tmp[0][i].se);
			ans = ans * seg.qry2(tmp[0][i].fi, tmp[0][i].se, 1, n, 1);
			an = mul(an, seg.qry3(tmp[0][i].fi, tmp[0][i].se, 1, n, 1));
		}
	//	de(id[3]);
		rep(i, 0, sz(tmp[1])) {
			de(tmp[1][i].fi);
			de(tmp[1][i].se);
			ans = ans * seg.qry(tmp[1][i].fi, tmp[1][i].se, 1, n, 1);
			an = mul(an, seg.qry3(tmp[1][i].fi, tmp[1][i].se, 1, n, 1));
		}
		ans = Mat();
		ans.set();
		ans = ans * mat[id[5]];
		ans = ans * mat[id[2]];
		ans = ans * mat[id[3]];
		rep(i, 0, ac.L) an = add(an, -ans.a[0][i]);
		cout << an << endl;
	}
	void build() {
		dfs(1, 0);
		dfs2(1, 0);
		dfs3(1, 0);
	}
}hc;
void add(int u, int v, string &s) {
	g[u].pb(v);
	G[u].pb(mp(v, s));
}
char s[44];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> q;
	rep(i, 1, n) {
		int u, v; string s; cin >> u >> v >> s;
		add(u, v, s);
		add(v, u, s);
	}
	rep(i, 1, m + 1) {
		cin >> s;
		ac.add(s);
	}
	ac.build();
	hc.build();
	seg.build(1, n, 1);
	rep(i, 1, q+1) {
		int u, v;
		cin >> u >> v;
		hc.qry(u, v);
	}
	return 0;
}
