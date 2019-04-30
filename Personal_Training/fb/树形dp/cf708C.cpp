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

const int N = 4e5 + 7;
int n, siz[N], u, v, suf[N], pre[N], f[N], h[N], mx, ans[N];
vi g[N];

void dfs(int u, int fa) {
	siz[u] = 1; f[u] = 0;
	int p = -1;
	rep(i, 0, sz(g[u])) if (g[u][i] == fa) p = i;
	if (p >= 0) g[u].erase(g[u].begin() + p); 
	for (auto v : g[u]) {
		dfs(v, u);
		siz[u] += siz[v];
		f[u] = max(f[u], f[v]);
		if (siz[v] <= mx) f[u] = max(f[u], siz[v]);
		pre[v] = f[u];
	}
	int t = 0;
	per(i, 0, sz(g[u])) {
		int v = g[u][i];
		t = max(t, f[v]);
		if (siz[v] <= mx) t = max(t, siz[v]);
		suf[v] = t;
	}
}

void dfs2(int u, int fa, int w) {
	h[u] = w;
	if (n - siz[u] <= mx) h[u] = max(h[u], n - siz[u]);
	rep(i, 0, sz(g[u])) {
		int v = g[u][i], t = h[u];
		if (i) t = max(t, pre[g[u][i-1]]);
		if (i + 1 < sz(g[u])) t = max(t, suf[g[u][i+1]]);
		dfs2(v, u, t);
	}
	bool ok = 1;
	if (n - siz[u] > mx) {
		if (n - siz[u] - h[u] > mx) ok = 0;
	}
	for (auto v : g[u]) if (siz[v] > mx && siz[v] - f[v] > mx) ok = 0;
	ans[u] = ok;
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n; 
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	mx = n / 2;
	dfs(1, 0);
	dfs2(1, 0, 0);
	rep(i, 1, n+1) cout << ans[i] << " \n"[i == n];
	return 0;
}


