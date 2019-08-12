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

int n, m, q, a[N];
vector<pair<int, string> > G[N];
vi g[N];

inline int add(int a, int b) {
	if((a += b) >= P) a -= P;
	assert(a < P && a > -P); 
	return a < 0 ? a + P : a;
}
inline int mul(int a, int b) {
	return 1ll * a * b % P;
}

vi ans;

struct AC {
	static const int N = 50, M = 26;
	int ne[N][M], fail[N], fa[N], rt, L, ed[N];
	void init() { rt = L++; fail[0] = N - 1;}
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
        rep(i, 0, L) {
			int j = i, ok = 0;
			while (j != 0) ok |= ed[j], j = fail[j];
			ed[i] |= ok;
		}
	}
}ac;



struct Mat {
	static const int N = 44;
	int n;
	int a[N][N];
	Mat() { n = ac.L;  rep(i, 0, N) rep(j, 0, N) a[i][j] = 0; }
	Mat operator * (const Mat &c) const {
		Mat r = Mat();
		rep(i, 0, n) rep(j, 0, n) rep(k, 0, n) 
			if (a[i][k] && c.a[k][j]) r.a[i][j] = add(r.a[i][j], mul(a[i][k], c.a[k][j]));
		return r;
	}
	vi operator * (const vi &c) const {
		vi r; r.resize(n, 0);
		rep(i, 0, n) rep(j, 0, n) r[i] = add(r[i], mul(a[i][j], c[j]));
		return r;
	}
	void print() {
		rep(i, 0, n) rep(j, 0, n) cout << a[i][j] << " \n"[j == n -1];
		cout << endl;
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
			return;
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
	void qry(int L, int R, int l, int r, int rt) {
		assert(l <= r);
		if(L <= l && r <= R) {
			ans = nd[rt] * ans;
			return;
		}
		int mid = l + r >> 1;
		if(R > mid) qry(L, R, mid + 1, r, rs);
		if(L <= mid) qry(L, R, l, mid, ls);
		return;
	}
	void qry2(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) {
			ans = dn[rt] * ans;
			return;
		}
		int mid = l + r >> 1;
		if(L <= mid) qry2(L, R, l, mid, ls);
		if(R > mid) qry2(L, R, mid + 1, r, rs);
		return;
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
		rep(j, 0, sz(G[c])) if(G[c][j].fi != fa) {
			int t = G[c][j].fi;
			int idt = id[t];
			a[idt] = sz(G[c][j].se);
			mat[idt].n = ac.L;
			rep(i, 0, ac.L) if (!ac.ed[i]){
//				for (auto u : G[c][j].se)
				rep(k, 0, sz(G[c][j].se)) {
					int x = ac.ne[i][G[c][j].se[k] - 'a'];
					if (!ac.ed[x]) {
						mat[idt].a[i][x]++;
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
		int o = 0;
		int fa = top[a], fb = top[b];
		while(fa != fb) {
			if(dep[fa] < dep[fb]) o ^= 1, swap(a, b), swap(fa, fb);
			tmp[o].pb(mp(id[fa], id[a]));
			a = par[fa], fa = top[a];
		}
		if(dep[a] < dep[b]) o ^= 1, swap(a, b);
		if (dep[a] != dep[b]) tmp[o].pb(mp(id[b]+1, id[a]));
		
		ans.resize(ac.L);
		rep(i, 0, ac.L) ans[i] = 1;
		ll an = 1;
		rep(i, 0, sz(tmp[1])) {
			//de(tmp[1][i].fi);
			//de(tmp[1][i].se);
			seg.qry(tmp[1][i].fi, tmp[1][i].se, 1, n, 1);
			an = mul(an, seg.qry3(tmp[1][i].fi, tmp[1][i].se, 1, n, 1));
		}
		per(i, 0, sz(tmp[0])) {
			//dd(tmp[0][i].fi);
			//de(tmp[0][i].se);
			seg.qry2(tmp[0][i].fi, tmp[0][i].se, 1, n, 1);
			an = mul(an, seg.qry3(tmp[0][i].fi, tmp[0][i].se, 1, n, 1));
		}
		an = add(an, -ans[0]);
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
	//freopen("a.in", "r", stdin);
	//freopen("a.out", "w", stdout); 
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> q;
	rep(i, 1, n) {
		int u, v; string s; cin >> u >> v >> s;
		add(u, v, s);
		add(v, u, s);
	}
	ac.init();
	rep(i, 1, m + 1) {
		cin >> s;
		ac.add(s);
	}
	ac.build();  
	hc.build();
//	return 0;
	seg.build(1, n, 1);
	//return 0;
	rep(i, 1, q+1) {
		int u, v;
		cin >> u >> v;
		hc.qry(u, v);
	}
	return 0;
}
