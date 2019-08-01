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
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {a = ((ll) a + b) % P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 101010;

ll n, f[2][N], g[2][N], tmp[N], sum[2][N];
vi h[N];

struct FW {
	static const int N = ::N;
	int n; ll a[N];
	void ini(int _n) {fill_n(a + 1, n = _n, 0);}
	void upd(int p, ll c) { for(; p <= n; p += (p & -p)) a[p] = add(a[p], c);}
	ll _qry(int p) {ll r = 0; for(; p; p -= (p & -p)) r = add(r, a[p]); return r;}
	ll qry(int l, int r) { return add(_qry(r), -_qry(l - 1)); }
} fw[2], F[2];

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
	void Build(vi g[]) {
		dfs(1, 0, g);
		_ = 0;
		dfs2(1, 0, g);
	}
	vector<pair<pii, int> > get(int u, int v) {
		int o = 0; vector<pair<pii, int> > tmp[2];
		while (top[u] != top[v]) {
			if (dep[top[u]] < dep[top[v]]) swap(u, v), o^= 1;
			tmp[o].pb(mp(mp(id[top[u]], id[u]), o));
			u = par[top[u]];
		}
		if (dep[u] < dep[v]) swap(u, v), o^= 1;
		tmp[o].pb(mp(mp(id[v], id[u]), o));
		reverse(all(tmp[1]));
		for (auto v : tmp[1]) tmp[0].pb(v);
		return tmp[0];
	}
}hc;

int ID(int o, int p) {
	if (o) return n - p + 1;
	return p;
}

void init() {
	hc.Build(h); 
	//rep(i, 1, n+1) de(hc.id[i]);
	rep(i, 1, n+1) tmp[hc.id[i]] = f[0][i];
	rep(i, 1, n+1) f[0][i] = tmp[i];
	reverse(tmp+1, tmp+n+1); 
	rep(i, 1, n+1) f[1][i] = tmp[i];
	rep(i, 1, n+1) tmp[hc.id[i]] = g[0][i];
	rep(i, 1, n+1) g[0][i] = tmp[i];
	reverse(tmp+1, tmp+n+1); 
	rep(i, 1, n+1) g[1][i] = tmp[i];
	//rep(i, 1, n+1) de(f[0][i]);
	rep(o, 0, 2) {
		fw[o].ini(n); F[o].ini(n);
		rep(i, 1, n+1) {
			sum[o][i] = add(sum[o][i-1], g[o][i]);
			fw[o].upd(i, mul(f[o][i], sum[o][i-1]));
			F[o].upd(i, f[o][i]);
		}
	}
}

int getG(int o, int l, int r) {if (l > r) return 0;return add(sum[o][r], -sum[o][l-1]);}

int cal(int o, int l, int r) {
	//dd(o), dd(l), de(r);
	int res = fw[o].qry(l, r);
	res = add(res, - mul(getG(o, 1, l-1), F[o].qry(l, r)));
	return res;
}

void solve() {
	cin >> n;
	rep(i, 1, n + 1) cin >> f[0][i];
	rep(i, 1, n + 1) cin >> g[0][i];
	rep(i, 1, n + 1) h[i].clear();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		h[u].pb(v); h[v].pb(u);
	}
	init();
	int q; cin >> q;
	while(q--) {
		int o;
		cin >> o;
		if(o == 1) {
			int s, t, x; cin >> s >> t >> x;
			vector<pair<pii, int> > tmp = hc.get(s, t);
			
			int ans = 0; 
			rep(j, 0, sz(tmp)) {
				int t = F[0].qry(tmp[j].fi.fi, tmp[j].fi.se);
				//de(t);
				ans = add(ans, mul(t, x));
				rep(i, 0, j) {
					//de(getG(0, tmp[i].fi.fi, tmp[i].fi.se));
					ans = add(ans, -mul(t, getG(0, tmp[i].fi.fi, tmp[i].fi.se)));
				}
			}
			//de(ans);
			rep(i, 0, sz(tmp)) {
				int l = tmp[i].fi.fi, r = tmp[i].fi.se, o = tmp[i].se; 
				//dd(l), dd(r), de(o);
				if (o) {
					ans = add(ans, -cal(o^1, l, r));
				}else {
					ans = add(ans, -cal(o^1, ID(o^1, r), ID(o^1, l)));
				}
			}
			cout << ans << endl;	
 		} else {
			int c, v; cin >> c >> v;
			c = hc.id[c];
			rep(i, 0, 2) {
				int t = ID(i, c);
				fw[i].upd(t, mul(v - f[i][t], sum[i][t-1]));
				F[i].upd(t, v - f[i][t]);
				f[i][t] = v;
			}
		}
	}
}

int main() {
	FI(a);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while (T--) solve();
	return 0;
}
