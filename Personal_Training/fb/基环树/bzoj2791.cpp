// 类似于基环树上求lca，分类讨论，注意自环 
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

const int N = 5e5 + 7;
int u, v, n, tim, dfn[N], fa[N], w, m, l, r, p, a[N], f[N][20], k, id[N], q, pos[N], d[N], x, y; 
bool in[N];
pii ans1, ans2, ans;
vi cir[N];
vector<pair<int, int> > g[N];

void dfs(int u, int pre) {
	dfn[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		if (g[u][i].se == pre) continue;
		int v = g[u][i].fi;
		if (dfn[v] && dfn[v] <= dfn[u]) {
			k++;
			int p = u; cir[k].pb(p); id[p] = k;
			if (p != v) {do { p = fa[p]; cir[k].pb(p); id[p] = k;
			} while (p != v);}
			if (sz(cir[k]) > 1 && a[cir[k][0]] != cir[k][1]) reverse(all(cir[k]));
			continue;
		}
		if (!dfn[v]) {fa[v] = u;dfs(v, g[u][i].se);}
	}
}

void dfs2(int u, int fa) {
	f[u][0] = fa;
	rep(j, 1, 20) f[u][j] = f[f[u][j-1]][j-1];
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi;
		if (v == fa || in[v]) continue;
		id[v] = id[u]; d[v] = d[u] + 1; dfs2(v, u);
	}
}

pii MIN(pii a, pii b) {
	int x = max(a.fi, a.se), y = max(b.fi, b.se);
	if (x != y) {
		if (x < y) return a;
		return b;
	}
	x = min(a.fi, a.se), y = min(b.fi, b.se);
	if (x != y) {
		if (x < y) return a;
		return b;
	}
	if (a.fi >= a.se) return a;
	return b;
}

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> q;
	rep(i, 1, n+1) {
		cin >> a[i];
		g[i].pb(mp(a[i], i));
		if (i != a[i]) g[a[i]].pb(mp(i, i));
	}
	rep(i, 1, n+1) if (!dfn[i]) {
		dfs(i, 0);
		m = sz(cir[k]);
		rep(j, 0, m) in[cir[k][j]] = 1, pos[cir[k][j]] = j;
		rep(j, 0, m) dfs2(cir[k][j], cir[k][j]);
	}
	rep(cas, 0, q) {
		cin >> u >> v;
		if (id[u] != id[v]) {
			cout << -1 << " " << -1 << endl;
		}else {
			if (in[u] || in[v] || (f[u][19] != f[v][19])) {
				x = d[u]; y = d[v];
				
				u = f[u][19]; v = f[v][19];
				if (pos[u] < pos[v]) {
					ans1 = mp(pos[v] - pos[u], 0);
					ans2 = mp(0, sz(cir[id[u]]) - (pos[v] - pos[u]));
				}else {
					ans1 = mp(sz(cir[id[u]]) - (pos[u] - pos[v]), 0);
					ans2 = mp(0, pos[u] - pos[v]);
				}
				ans1.fi += x; ans1.se += y;
				ans2.fi += x; ans2.se += y;
			}else {
				x = y = 0;
				per(i, 0, 20) {
					if (d[v] - d[u] - pw(i) >= 0) {
						v = f[v][i];
						y += pw(i);
					}
					if (d[u] - d[v] - pw(i) >= 0) {
						u = f[u][i];
						x += pw(i);
					}
				}
				per(i, 0, 20) if (f[u][i] != f[v][i]){
					u = f[u][i]; v = f[v][i];
					x += pw(i); y += pw(i);
				}
				if (u != v) x++, y++;
				ans1 = ans2 = mp(x, y);
			}
			ans = MIN(ans1, ans2);
			cout << ans.fi << " " << ans.se << endl;
		}
	}
	return 0;
}


