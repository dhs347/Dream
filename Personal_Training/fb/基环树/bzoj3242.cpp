// 求边上一点到基环树最远点距离最小 
// 可以转化成基环树断一条环边使直径最小 
// 分类讨论，处理选的两点在断掉一边和分在两边的情况 
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

const int N = 1e5 + 76;
int vis[N], dfn[N], fa[N], in[N], n, u, v, val, tim, len;
ll  d[N], s[N], c[N], e[N], ans, w[N], ans2, t0[N], t1[N], ma;
vector<pair<pii, int> > g[N]; 
vi cir;

void dfs(int u, int pre) {
	dfn[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		if (g[u][i].se == pre) continue;
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (dfn[v] && dfn[v] <= dfn[u]) {
			len = w;
			int p = u; cir.pb(p);
			if (p != v) {do { p = fa[p]; cir.pb(p);
			} while (p != v);}
			reverse(all(cir));
			continue;
		}
		if (!dfn[v]) {fa[v] = u; d[v] = d[u] + w; dfs(v, g[u][i].se);}
	}
}


ll dfs2(int u, int fa) {
	ll res = 0;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (in[v] || v == fa) continue; 
		ll tmp = dfs2(v, u) + w;
		ans2 = max(ans2, res + tmp);
		res = max(res, tmp); 
	}
	return res;
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(1);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> u >> v >> val;
		g[u].pb(mp(mp(v, val), i));
		g[v].pb(mp(mp(u, val), i));
	}
	dfs(1, -1);
	n = sz(cir);
	rep(i, 0, n) in[cir[i]] = 1;
	rep(i, 0, n) w[i] = dfs2(cir[i], -1);
	rep(i, 0, n) s[i] = d[cir[i]] - d[cir[0]];
	s[n] = s[n-1] + len; 
	ma = 0;
	rep(i, 0, n) {
		c[i] = i == 0 ? w[0] : max(c[i-1], s[i] + w[i] + ma);
		ma = max(ma, w[i] - s[i]);
	}
	ma = 0;
	per(i, 0, n) {
		e[i] = i == n - 1 ? w[0] : max(e[i+1], ma + w[i] - s[i]);
		ma = max(ma, w[i] + s[i]);
	}
	rep(i, 0, n) t0[i] = i == 0 ? w[i] + s[i] : max(t0[i-1], w[i] + s[i]);
	per(i, 0, n) t1[i] = i == n - 1 ? w[i] + s[n] - s[i] : max(t1[i+1], w[i] + s[n] - s[i]);
	ans = pw(60);
	rep(i, 0, n) {
		ll tmp;
		tmp = i == 0 ? e[i] : max(max(c[i-1], e[i]), t0[i-1] + t1[i]);
		ans = min(ans, tmp);
	}
	cout << max(ans, ans2) / 2.0;	
	return 0;
}


