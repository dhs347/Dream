#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

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
	inline void wll(ll x) {
		if (x < 0) wchar('-'), x = -x;
		char s[24];
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

struct P {
	int x, y;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	void read() { x = io.xint(), y = io.xint(); }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
};

ll det(P a, P b) { return a.x * 1ll * b.y - a.y * 1ll * b.x; }

int n, m, q;
vector<P> ps;
vector<pii> es;

namespace Planar {
	static const int N = 2e6 + 7, M = 2e6 + 7;
	// ps id starts from 0
	vector<P> ps;
	// cnte id starts from 0
	int cnte, ne[M];
	bool vis[M];
	// u -> (v, cnte)
	vector<pii> g[N];
	pii E[M];
	int cntp, belong[M];
	ll area[M];
	int rt, dep[M];
	vector<pii> G[M];
	ll sum[M], cnt[M];
	bool dfs_vis[M];
	vector<pair<pii, int> > EE;

	void init() {
		rep(i, 0, sz(ps)) g[i].clear();
		rep(i, 0, cntp) G[i].clear();
		fill_n(vis, cnte, false);
		fill_n(dfs_vis, cntp, false);
		ps.clear(); cnte = cntp = 0;
		EE.clear();
	}
	void _add(int u, int v) {
		g[u].pb(mp(v, cnte));
		EE.pb(mp(mp(u, v), cnte));
		E[cnte++] = mp(u, v);
	}
	void adde(int u, int v) { _add(u, v), _add(v, u); }
	int V;
	bool cmp(const pii &i, const pii &j) {
		P a = ps[i.fi] - ps[V], b = ps[j.fi] - ps[V];
		int o = P(0, 0) < a, t = P(0, 0) < b;
		if(o != t) return o < t;
		return det(a, b) > 0;
	}
	void go(int e) {
		ll &A = area[cntp];
		while(!vis[e]) {
			A += det(ps[E[e].se], ps[E[e].fi]);
			vis[e] = 1;
			e = ne[e ^ 1];
			belong[e] = cntp;
		}
		if(A < 0) rt = cntp;
		cntp++;
	}
	void dfs(int u, int d) {
		ll A = area[u];
		sum[u] = A * A, cnt[u] = A;
		dep[u] = d;
		dfs_vis[u] = 1;
		rep(i, 0, sz(G[u])) {
			pii v = G[u][i];
			if(!dfs_vis[v.fi]) {
				dfs(v.fi, d + 1);
				vis[v.se] = vis[v.se ^ 1] = 0;
				sum[u] += sum[v.fi];
				cnt[u] += cnt[v.fi];
			}
		}
	}
	void solve(const vector<P> &_ps, const vector<pii> &es) {
		init(); ps = _ps;
		rep(i, 0, sz(es)) {
			pii e = es[i];
			adde(e.fi, e.se);
		}
		rep(i, 0, sz(ps)) {
			V = i; sort(all(g[i]), cmp);
			rep(j, 0, sz(g[i])) {
				ne[g[i][j].se] = g[i][(j + 1) % sz(g[i])].se;
			}
		}
		rep(i, 0, cnte) if(!vis[i]) go(i);
		rep(i, 0, cnte) if(i & 1) {
			int u = belong[i - 1], v = belong[i];
			G[u].pb(mp(v, i - 1)), G[v].pb(mp(u, i));
		}
		dfs(rt, 1);
		ll p = 0, q = 0;
		sort(all(EE));
		rep(i, 0, ::q) {
			int c = io.xint();
			int d = (c + p) % n + 1;
			vi vec; rep(j, 0, d) {
				int x = io.xint(); x = (x + p) % n;
				vec.pb(x);
			}
			p = 0, q = 0;
			rep(i, 0, sz(vec)) {
				int u = vec[i], v = vec[(i + 1) % sz(vec)];
				int pos = lower_bound(all(EE), mp(mp(u, v), 0)) - EE.begin();
				int e = EE[pos].se;
				if(!vis[e]) {
					int t = belong[e], o = belong[e ^ 1];
					if(dep[t] < dep[o]) {
						p -= sum[o], q -= cnt[o];
					} else {
						p += sum[t], q += cnt[t];
					}
				}
			}
			ll g = __gcd(p, q); p /= g, q /= g; 
			if(p % 2 == 0) p >>= 1; else q <<= 1;
			io.wll(p);
			io.wchar(' ');
			io.wll(q);
			io.wchar('\n');
		}
	}
}

int main() {
	n = io.xint();
	m = io.xint();
	q = io.xint();
	rep(i, 1, n + 1) {
		P p; p.read();
		ps.pb(p);
	}
	rep(i, 1, m + 1) {
		int u = io.xint(), v = io.xint();
		es.pb(mp(u - 1, v - 1));
	}
	Planar::solve(ps, es);
	return 0;
}
