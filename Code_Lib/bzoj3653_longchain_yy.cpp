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

const int N = 303030, M = 1e7;

int n, m, cntL;
int dep[N], sz[N], rt[N], ls[M], rs[M];
ll ans[N], sum[M];
vi g[N];
vector<pii> Q[N];

// read untill EOF (xint)
struct FastIO {
	static const int S = 1310720;
	int wpos;
	char wbuf[S];
	bool ed;
	FastIO() : wpos(0), ed(0) { }
	inline int xchar() {
		static char buf[S];
		static int len = 0, pos = 0;
		if (pos == len) pos = 0, len = fread(buf, 1, S, stdin);
		if (pos == len) return -1;
		return buf[pos++];
	}
	inline int xint() {
		int c = xchar(), x = 0, s = 1;
		while (c <= 32) {
			if(!~c) return ed = 1;
			c = xchar();
		}
		if (c == '-') s = -1, c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x * s;
	}
	inline int xuint() {
		int c = xchar(), x = 0;
		while (c <= 32) c = xchar();
		for (; '0' <= c && c <= '9'; c = xchar()) x = x * 10 + c - '0';
		return x;
	}
	inline void xstring(char *s) {
		int c = xchar();
		while (c <= 32) c = xchar();
		for (; c >  32; c = xchar()) *s++ = c;
		*s = 0;
	}
	inline void wchar(int x) {
		if (wpos == S) fwrite(wbuf, 1, S, stdout), wpos = 0;
		wbuf[wpos++] = x;
	}
	inline void wint(ll x) {
		if (x < 0) wchar('-'), x = -x;
		char s[48];
		int n = 0;
		while (x || !n) s[n++] = '0' + x % 10, x /= 10;
		while (n--) wchar(s[n]);
	}
	inline void wstring(const char *s) {
		while (*s) wchar(*s++);
	}
	~FastIO() {
		if (wpos) fwrite(wbuf, 1, wpos, stdout), wpos = 0;
	}
} io;

struct LC {
	static const int N = ::N;
	int wson[N], top[N], dep[N], id[N], who[N], _;
	ll sum[N];
	void dfs(int c, int fa, vi g[]) {
		::dep[c] = ::dep[fa] + 1;
		::sz[c] = 1;
		dep[c] = 1; int &s = wson[c] = top[c] = 0;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t != fa) {
				dfs(t, c, g);
				dep[c] = max(dep[c], dep[t] + 1);
				(dep[t] >= dep[s]) && (s = t);
				::sz[c] += ::sz[t];
			}
		}
	}
	void dfs2(int c, int fa, vi g[]) {
		if(!top[c]) top[c] = c;
		who[id[c] = ++_] = c;
		int s = wson[c];
		if(s) top[s] = top[c], dfs2(s, c, g);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t != fa && t != s) dfs2(t, c, g);
		}
	}
	void build(vi g[]) {
		dfs(1, 0, g);
		_ = 0;
		dfs2(1, 0, g);
	}
	void solve(int u, int fa, vi g[]) {
		rep(i, 0, sz(g[u])) if(g[u][i] != fa) solve(g[u][i], u, g);
		rep(i, 0, sz(g[u])) {
			int v = g[u][i];
			if(v != fa && v != wson[u]) {
				int d = dep[v];
				int p = id[wson[u]], q = id[v];
				while(d--) {
					sum[p] += sum[q];
					p++, q++;
				}
			}
		}
		if(wson[u]) {
			sum[id[u]] = sum[id[u] + 1] + sz[u] - 1;
		} else {
			sum[id[u]] = sz[u] - 1;
		}
		if(wson[u]) rep(i, 0, sz(Q[u])) {
			int L = id[u] + 1, R = L + Q[u][i].fi - 1;
			if(Q[u][i].fi + 1 >= dep[u]) ans[Q[u][i].se] += sum[L];
			else ans[Q[u][i].se] += sum[L] - sum[R + 1];
		}
	}
}lc;

int main() {
	n = io.xint();
	m = io.xint();
	rep(i, 1, n) {
		int u, v;
		u = io.xint();
		v = io.xint();
		g[u].pb(v), g[v].pb(u);
	}
	dep[0] = -1;
	lc.build(g);
	rep(i, 1, m + 1) {
		int p, k;
		p = io.xint();
		k = io.xint();
		ans[i] = min(dep[p], k) * 1ll * (sz[p] - 1);
		Q[p].pb(mp(k, i));
	}
	lc.solve(1, 0, g);
	rep(i, 1, m + 1) io.wint(ans[i]), io.wchar('\n');
	return 0;
}
