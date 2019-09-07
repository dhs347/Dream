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

const int N = 1e6 + 7;

int n, q, a[N], par[N], dep[N], st[N], ed[N], dfn;
ll ans[N];
vi g[N];
vector<pair<int, pii> > vec[N];
int nn;

struct FW {
	static const int N = ::N;
	ll sum[N];
#define lb(x) ((x)&-(x))
	void upd(int p, ll c) {
		for(; p <= n; p += lb(p)) sum[p] += c;
	}
	ll _qry(int p) {
		ll r = 0;
		for(; p; p ^= lb(p)) r += sum[p];
		return r;
	}
	ll qry(int l, int r) {
		return _qry(r) - _qry(l - 1);
	}
}fw;

void add(int v, int i, int k) {
	//dd(v), dd(i), de(k);
	int l = dep[v], r = min(dep[v] + k, nn);
	vec[r].pb(mp(i, mp(st[v], ed[v])));
//	dd(l), dd(r), dd(i), dd(st[v]), de(ed[v]);
	vec[l - 1].pb(mp(-i, mp(st[v], ed[v])));
}
void dfs(int u, int fa) {
	st[u] = ++dfn;
	par[u] = fa;
	dep[u] = dep[fa] + 1;
	nn = max(nn, dep[u]);
	for(auto v : g[u]) if(v != fa) dfs(v, u);
	ed[u] = dfn;
}
struct FI {
	static const int S = 1e7;
	int wpos;
	char wbuf[S];
	bool ed;
	FI() : wpos(0), ed(0) {}
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0; 
		if(pos == len) pos = 0, len = fread(buf, 1, S, stdin);
		if(pos == len) return -1;
		return buf[pos++];
	}
	inline int xint() {
		int c = xchar(), x = 0, s = 1;
		while(c <= 32) {
			if(!~c) return ed = 1;
			c = xchar();
		}
		if(c == '-') s = -1, c = xchar();
		for(; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline void wchar(int x) {
		if(wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wll(ll x) {
		if(x < 0) wchar('-'), x = -x;
		char s[22];
		int n = 0;
		while(x || !n) s[n++] = '0' + x % 10, x /= 10;
		while(n--) wchar(s[n]);
	}
	~FI() {
		if(wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
}io;
int main() {
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	cin >> q;
	rep(i, 1, q + 1) {
		int v, k; cin >> v >> k; int u = v;
		while(k >= 0 && v) {
			if(u == v) {
				add(v, i, k);
			} else {
				add(v, i, k);
				if(k) add(u, -i, k - 1);
			}
			u = v, v = par[v], --k;
		}
	}
	vi que; que.pb(1);
	rep(i, 0, sz(que)) {
		int u = que[i]; 
		for(auto v : g[u]) if(v != par[u]) que.pb(v);
	}
//	de(sz(que));
	rep(i, 0, sz(que)) {
		int u = que[i];
		fw.upd(st[u], a[u]);
		if(i == sz(que) - 1 || dep[que[i]] != dep[que[i + 1]]) {
			int d = dep[u];
			for(auto t : vec[d]) {
				auto ret = fw.qry(t.se.fi, t.se.se);
				int o = t.fi > 0 ? 1 : -1;
				ans[abs(t.fi)] += o * ret;
			}
		}
	}
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
