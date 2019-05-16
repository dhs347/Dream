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
vector<pair<pii, int> > Q[N];

void dfs(int u, int fa) {
	dep[u] = dep[fa] + 1;
	sz[u] = 1;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if(v != fa) {
			dfs(v, u);
			sz[u] += sz[v];
		}
	}
}
void upd(int p, int c, int l, int r, int &rt) {
	if(!rt) rt = ++cntL;
	sum[rt] += c;
	if(l == r) return ;
	int mid = l + r >> 1;
	if(p <= mid) upd(p, c, l, mid, ls[rt]);
	else upd(p, c, mid + 1, r, rs[rt]);
}
int merge(int x, int y) {
	if(x && y) {
		sum[x] += sum[y];
		ls[x] = merge(ls[x], ls[y]);
		rs[x] = merge(rs[x], rs[y]);
		return x;
	} else {
		return x + y;
	}
}
ll qry(int L, int R, int l, int r, int rt) {
	if(!rt) return 0;
	if(L <= l && r <= R) return sum[rt];
	int mid = l + r >> 1;
	ll ans = 0;
	if(L <= mid) ans += qry(L, R, l, mid, ls[rt]);
	if(R > mid) ans += qry(L, R, mid + 1, r, rs[rt]);
	return ans;
}
void solve(int u, int fa) {
	if(dep[u]) upd(dep[u], sz[u] - 1, 1, n, rt[u]);
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if(v != fa) {
			solve(v, u);
			rt[u] = merge(rt[u], rt[v]);
		}
	}
	rep(i, 0, sz(Q[u])) {
		ans[Q[u][i].se] += qry(Q[u][i].fi.fi, Q[u][i].fi.se, 1, n, rt[u]);
	}
}

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
	dfs(1, 0);
	rep(i, 1, m + 1) {
		int p, k;
		p = io.xint();
		k = io.xint();
		ans[i] = min(dep[p], k) * 1ll * (sz[p] - 1);
		Q[p].pb(mp(mp(min(n, dep[p] + 1), min(n, dep[p] + k)), i));
	}
	solve(1, 0);
	rep(i, 1, m + 1) io.wint(ans[i]), io.wchar('\n');
	return 0;
}
