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
int par[N], val[N];
vi g[N], G[N];

struct FW {
#define lb(x) ((x)&-(x))
	int n; vi a;
	void init(int _n) {
		n = _n;
		a = vi(n + 1);
	}
	void upd(int p, int c) {
		for( ; p <= n; p += lb(p)) a[p] += c;
	}
	int qry(int p) {
		if(p < 1) return 0;
		p = min(p, n);
		int ans = 0;
		for( ; p; p ^= lb(p)) ans += a[p];
		return ans;
	}
}fw[N], ch[N];

// N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
	static const int N = 101010 << 1;
	int a[20][N] , lft[N] , dep[N] , lg[N] , L;
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa,const vi g[]){
		lft[c]=L;add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
		}
	}
	void Build(const vi g[]){
		L = 0;dfs(1,0,g);dep[0] = -1;
		rep(i,2,L) lg[i]=lg[i>>1]+1;
		rep(i,1,20){
			int lim = L+1-(1<<i);
			rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
		}
	}
	int lca(int x,int y){
		x = lft[x] , y = lft[y];
		if(x > y) swap(x , y);
		int i = lg[y-x+1];
		return rmin(a[i][x] , a[i][y+1-(1<<i)]);
	}
	int dis(int x, int y) {
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}
}R;

// id starts from 1
namespace Centriod {
	const int N = ::N;
	bool vis[N];
	int sz[N];
	vector<int> vec[N];
	void dfssz(int c,int fa,int Sz,int &rt){
		sz[c] = 1;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
		}
		if(!rt && sz[c]*2>Sz) rt=c;
	}
	void dfs(int u, int rt, int tp) {
		int dep = R.dis(u, rt);
		while(sz(vec[tp]) < dep + 1) vec[tp].pb(0);
		vec[tp][dep] += val[u];
		rep(i, 0, sz(G[u])) dfs(G[u][i], rt, tp);
	}
	int dfs(int c){
		int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
		vis[rt] = true;
		int u = rt;
		rep(i, 0, sz(g[rt])) {
			int v = g[rt][i];
			if(!vis[v]) {
				int t = dfs(v);
				G[rt].pb(t);
				par[t] = rt;
			}
		}
		int ma = 0;
		rep(i, 0, sz(G[rt])) {
			int v = G[rt][i];
			vec[v].clear();
			vec[v].pb(0);
			dfs(v, rt, v);
			ch[v].init(sz(vec[v]) - 1);
			ma = max(ma, sz(vec[v]) - 1);
		}
		fw[u].init(ma);
		rep(i, 0, sz(G[rt])) {
			int v = G[rt][i];
			rep(j, 1, sz(vec[v])) {
				ch[v].upd(j, vec[v][j]);
				fw[u].upd(j, vec[v][j]);
			}
		}
		return rt;
	}
};

int qry(int p, int v, int u, int k) {
	if(v == u) {
		return fw[u].qry(k) + val[u];
	} else {
		k -= R.dis(p, u);
		if(k < 0) return 0;
		return val[u] + fw[u].qry(k) - ch[v].qry(k);
	}
}

void upd(int p, int v, int u, int c) {
	if(v == u) {
	} else {
		int dep = R.dis(p, u);
		fw[u].upd(dep, c);
		ch[v].upd(dep, c);
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
	inline void wint(int x) {
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

int main() {
	n = io.xint();
	m = io.xint();
	rep(i, 1, n + 1) val[i] = io.xint();
	rep(i, 1, n) {
		int u, v;
		u = io.xint();
		v = io.xint();
		g[u].pb(v), g[v].pb(u);
	}
	R.Build(g);
	int rt = Centriod::dfs(1), ans = 0;
	while(m--) {
		int o, x, y;
		o = io.xint();
		x = io.xint();
		y = io.xint();
		x ^= ans, y ^= ans;
		if(o == 0) {
			int p = x, v = x, u = x;
			ans = 0;
			while(1) {
				ans += qry(p, v, u, y);
				if(u == rt) break;
				v = u, u = par[u];
			}
			io.wint(ans);
			io.wchar('\n');
		} else {
			int c = y - val[x];
			val[x] = y;
			int p = x, v = x, u = x;
			while(1) {
				upd(p, v, u, c);
				if(u == rt) break;
				v = u, u = par[u];
			}
		}
	}
	return 0;
}
