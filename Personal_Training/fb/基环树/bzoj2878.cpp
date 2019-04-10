// 求基环树上任意起点走的路径长度期望 
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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a;}
int sub(int a, int b) {if((a -= b) < 0) a += P; return a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;

int dfn[N], tim, n, m, u, v, w, fa[N], root;
bool vis[N], in[N], ok;
db b[N], c[N], ans[N], sum, cc[N];
vi cir;
vector<pair<pii, int> > g[N];

void dfs(int u, int pre) {
	dfn[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		if (g[u][i].se == pre) continue;
		int v = g[u][i].fi.fi;
		if (dfn[v] && dfn[v] <= dfn[u]) {
			int p = u; cir.pb(p); 
			if (p != v) {do { p = fa[p]; cir.pb(p);
			} while (p != v);}
			continue;
		}
		if (!dfn[v]) {fa[v] = u;dfs(v, g[u][i].se);}
	}
}

void dfs2(int u, int fa) {
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (v == fa || in[v]) continue;
		dfs2(v, u);
		int du = sz(g[u]);
		if (in[u]) du -= 2;
		else if (u != root) du -= 1;
 		b[u] += (b[v] + w) / du; 
	}
}

void dfs3(int u) {
	vis[u] = 1;
	int d1 = 0, d2 = 0;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (vis[v]) continue;
		if (in[v]) d1++;else d2++;
		if (in[v]) {
			dfs3(v);
 			c[u] += (c[v] + w);
			c[v] = 0; 
		}
	}
	if (d1 + d2 > 0 && u != root) {
		c[u] = c[u] * d1 + b[u] * d2;
		c[u] /= (d1 + d2);
	}
	vis[u] = 0; 
}

void dfs4(int u, int fa, db pre) {
	if (u == root) {
		if (ok) ans[u] = (cc[u] + b[u] * (sz(g[u]) - 2)) / sz(g[u]);
		else ans[u] = b[u];
	}
	else {
		ans[u] = (b[u] * (sz(g[u])-1) + pre) / sz(g[u]);
	}
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (v == fa || in[v]) continue;
		int du = sz(g[u]); db tmp = ans[u];
		if (du == 1) tmp = 0;else tmp = (tmp * du - w - b[v]) / (du - 1);
		dfs4(v, u, tmp + w); 
	}
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(5);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> u >> v >> w;
		g[u].pb(mp(mp(v, w), i));
		g[v].pb(mp(mp(u, w), i));
	}
	ok = (n == m);
	if (ok) {
		dfs(1, -1);
		rep(i, 0, sz(cir)) in[cir[i]] = 1;
		rep(i, 0, sz(cir)) root = cir[i], dfs2(cir[i], 0); 
		rep(i, 0, sz(cir)) {
			root = cir[i], dfs3(cir[i]); 
			cc[cir[i]] = c[cir[i]];
			c[cir[i]] = 0;
		}
		rep(i, 0, sz(cir)) root = cir[i], dfs4(cir[i], 0, 0);
	}else {
		root = 1;dfs2(1, 0);
		dfs4(1, 0, 0);
	}
	rep(i, 1, n+1) sum += ans[i];
	cout << sum / n << endl; 
	return 0;
}

