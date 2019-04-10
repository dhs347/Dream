// 求基环树的直径 
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

const int N = 1e6 + 7;
int u, v, n, tim, dfn[N], fa[N], w, m, l, r, p; 
ll d[N], f[N], ans, sum, a[N], W;
bool in[N];
pair<ll, int> q[N];
vi cir;
vector<pair<pii, int> > g[N];

void dfs(int u, int pre) {
	dfn[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		if (g[u][i].se == pre) continue;
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (dfn[v] && dfn[v] < dfn[u]) {
			W = w;
			int p = u; cir.pb(p);
			do { p = fa[p]; cir.pb(p);
			} while (p != v);
			reverse(all(cir));
			continue;
		}
		if (!dfn[v]) {fa[v] = u, d[v] = d[u] + w; dfs(v, g[u][i].se);}
	}
}

void dfs2(int u, int fa) {
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi.fi, w = g[u][i].fi.se;
		if (v == fa || in[v]) continue;
		dfs2(v, u);
		f[u] = max(f[u], a[u] + a[v] + w);
		ans = max(ans, f[u]);
		a[u] = max(a[u], a[v] + w);
	}
}

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> u >> w;
		g[i].pb(mp(mp(u, w), i));
		g[u].pb(mp(mp(i, w), i));
	}
	rep(i, 1, n+1) if (!dfn[i]) {
		cir.clear();
		dfs(i, 0);
		m = sz(cir); ans = 0;
		rep(j, 0, m) in[cir[j]] = 1;
		rep(j, 0, m) dfs2(cir[j], 0);
		W += d[cir[m-1]] - d[cir[0]];
		l = 0; r = 0; p = 0;
		rep(j, m, 2 * m) {
			while (p < j) {
				ll val = p < m ? a[cir[p]] - d[cir[p]] : a[cir[p-m]] - d[cir[p-m]] - W;
				while (l < r && q[r-1].fi <= val) r--;
				q[r++] = mp(val, p);
				p++;
			}
			while (l < r && q[l].se <= j - m) l++;
			ans = max(ans, a[cir[j-m]] + d[cir[j-m]] + q[l].fi + W);
		}
		sum += ans;
	}
	cout << sum << endl;
	return 0;
}


