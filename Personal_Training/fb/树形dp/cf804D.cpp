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
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;
vi g[N];
int f[N], h[N], vis[N], id[N], k, D[N], suf[N], pre[N], n, m, q, u, v;
vector<ll> tmp[N], Suf[N];
map<pii, db> M;

void dfs(int u) {
	vis[u] = 1;
	int p = -1; tmp[k].pb(u); id[u] = k;
	rep(i, 0, sz(g[u])) if (vis[g[u][i]]) {p = i;break;}
	if (p >= 0) g[u].erase(g[u].begin() + p); 
	for (auto v : g[u]) {
		dfs(v);
		D[k] = max(D[k], f[u] + f[v] + 1);
		f[u] = max(f[u], f[v] + 1);
		suf[v] = pre[v] = f[v] + 1;
	}
	rep(i, 1, sz(g[u])) {
		int v = g[u][i];
		pre[v] = max(pre[v], pre[g[u][i-1]]);
	} 
	per(i, 0, sz(g[u]) - 1) {
		int v = g[u][i];
		suf[v] = max(suf[v], suf[g[u][i+1]]);
	}
}

void dfs2(int u, int w) {
	h[u] = w + 1;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i], t = h[u];
		if (i) t = max(t, pre[g[u][i-1]]);
		if (i + 1 < sz(g[u])) t = max(t, suf[g[u][i+1]]);
		dfs2(v, t);
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(8);
	cin >> n >> m >> q;
	rep(i, 1, m+1) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i, 1, n+1) if (!vis[i]) {
		k++; dfs(i); dfs2(i, -1);
		rep(i, 0, sz(tmp[k])) tmp[k][i] = max(f[tmp[k][i]], h[tmp[k][i]]);
		sort(all(tmp[k])); 
		Suf[k] = tmp[k];
		per(i, 0, sz(Suf[k]) - 1) Suf[k][i] += Suf[k][i+1];
	}
	rep(cas, 0, q) {
		cin >> u >> v;
		u = id[u]; v = id[v];
		if (u == v) cout << -1 << endl;
		else {
			if (sz(tmp[u]) > sz(tmp[v]) || (sz(tmp[u]) == sz(tmp[v]) && u > v)) swap(u, v); 
			if (M.count(mp(u, v))) {
				cout << M[mp(u, v)] << endl;
				continue;
			}
			int t = max(D[u], D[v]); db ans = 0;
			rep(i, 0, sz(tmp[u])) {
				int p = upper_bound(all(tmp[v]), t - 1 - tmp[u][i]) - tmp[v].begin();
				ans += 1ll * t * p + 1ll * (sz(tmp[v]) - p) * (tmp[u][i] + 1) + (p == sz(tmp[v]) ? 0 : Suf[v][p]);
			}
			ans = ans / sz(tmp[u]) / sz(tmp[v]);
			M[mp(u, v)] = ans;
			cout << ans << endl;
		}
	}
	return 0;
}


