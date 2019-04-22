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

int n, u, v, w;
db pre[N], suf[N];
db f[N], p[N], ans;
vector<pair<int, db> > g[N];


void dfs1(int u, int fa) {
	int t = -1; f[u] = 1;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi; db w = g[u][i].se;
		if (v == fa) {t = i; continue;}
		dfs1(v, u);
		f[u] *= f[v] + (1 - f[v]) * w;
	}
	if (t >= 0) g[u].erase(g[u].begin() + t); 
	db tmp = 1;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi; db w = g[u][i].se;
		tmp *= f[v] + (1 - f[v]) * w;
		pre[v] = tmp;
	}
	tmp = 1;
	per(i, 0, sz(g[u])) {
		int v = g[u][i].fi; db w = g[u][i].se;
		tmp *= f[v] + (1 - f[v]) * w;
		suf[v] = tmp;
	}
	f[u] *= (1 - p[u]);
}

void dfs2(int u, db tmp, db w) {
	db x = tmp + (1 - tmp) * w;
	ans += 1 - f[u] * x;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi;
		db t = x;
		if (i) t *= pre[g[u][i-1].fi];
		if (i + 1 < sz(g[u])) t *= suf[g[u][i+1].fi];
		dfs2(v, t * (1 - p[u]), g[u][i].se);
	}
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v >> w;
		g[u].pb(mp(v, 1 - 1.0 * w / 100));
		g[v].pb(mp(u, 1 - 1.0 * w / 100));
	}
	rep(i, 1, n+1) cin >> p[i], p[i] /= 100;
	dfs1(1, 0);
	dfs2(1, 1, 0);
	cout << ans << endl;
	return 0;
}

