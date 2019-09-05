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
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef uniform_int_distribution<ll> RR;
mt19937 gen(998244353);
ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
//----

const int N = 1e5 + 7;

vi revg[N], g[N], buf[N], ord;
int stamp, vis[N], dfn[N], fa[N];
int fs[N], mins[N], dom[N], sem[N], buf2[N];

void dfs(int u) {
	vis[u] = stamp; dfn[u] = sz(ord); ord.pb(u);
	for (auto v : g[u]) if (vis[v] != stamp) fa[v] = u, dfs(v);
}

int find(int u) {
	if (u == fs[u]) return u;
	int v = fs[u];
	fs[u] = find(fs[u]);
	if (~mins[v] && dfn[sem[mins[v]]] < dfn[sem[mins[u]]]) mins[u] = mins[v];
	return fs[u];
}

void mark(int s) {
	ord.clear(); ++stamp; dfs(s);
	for (auto u : ord) fs[u] = u, mins[u] = buf2[u] = -1;
	per(i, 1, sz(ord)) {
		int u = ord[i], p = fa[u]; sem[u] = p;
		for(auto v : revg[u]) if (vis[v] == stamp) {
			if (dfn[v] > dfn[u]) find(v), v = sem[mins[v]];
			if (dfn[v] < dfn[sem[u]]) sem[u] = v;
		}
		buf[sem[u]].pb(u); mins[u] = u; fs[u] = p;
		per(j, 0, sz(buf[p])) {
			int v = buf[p][j]; find(v);
			if (sem[v] == sem[mins[v]]) dom[v] = sem[v]; else buf2[v] = mins[v];
		}
		buf[p].clear();
	}
	dom[ord[0]] = ord[0];
	for (auto u : ord) if (~buf2[u]) dom[u] = dom[buf2[u]];
}

int n, u, v, siz[N];
vi gg[N];

void dfs2(int u) {
	siz[u] = 1;
	for (auto v : gg[u]) {
		dfs2(v);
		siz[u] += siz[v];
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) {
		while (cin >> u) {
			if (u == 0) break;
			g[u].pb(i);
			revg[i].pb(u);
		}
	} 
	n++;
	rep(i, 1, n) if (sz(revg[i]) == 0) {
		g[n].pb(i);
		revg[i].pb(n);
	}
	mark(n);
	rep(i, 1, n) gg[dom[i]].pb(i);
	dfs2(n);
	rep(i, 1, n) cout << siz[i] - 1 << endl; 
	return 0;
}


