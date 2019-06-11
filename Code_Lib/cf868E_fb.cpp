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

const int N = 55;
int b[N], a[N], f[N], n, u, v, w, s, m, x;
ll h[N][N][N][N], ans;
vector<pii> g[N];

void dfs(int u, int fa) {
	b[u] = a[u];
	f[u] = fa;
	for (auto v : g[u]) {
		if (v.fi == fa) continue;
		dfs(v.fi, u);
		b[u] += b[v.fi];
	}
}

ll solve(int u, int fa, int c1, int c2) {
	if (sz(g[u]) == 1) c2 -= c1, c1 = 0;
	if (c2 == 0) return 0;
	if (h[u][fa][c1][c2] != -1) return h[u][fa][c1][c2];
	ll &t = h[u][fa][c1][c2];
	if (sz(g[u]) == 1 || c1 == 0) return t = solve(fa, u, c2, c2) + g[u][0].se;
	ll dp[N] = {pw(60)}, cnt = 0;
	for (auto v : g[u]) {
		if (v.fi == fa) continue;
		per(i, 1, c1+1) {
			if (!cnt) dp[i] = solve(v.fi, u, i, c2) + v.se;
			else { 
				rep(j, 1, i+1) dp[i] = max(dp[i], min(dp[i-j], solve(v.fi, u, j, c2) + v.se));
			}
		}
		cnt++;
	}
	return t = dp[c1];
}

int main() {
	freopen("a.in","r",stdin);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	cin >> s >> m;
	rep(i, 1, m+1) cin >> x, a[x]++;
	a[s] = 0;
	dfs(1, 0);
	ans = pw(60);
	memset(h, -1, sizeof(h));
	for (auto v : g[s]) 
		ans = min(ans, solve(v.fi, s, v.fi != f[s] ? b[v.fi] : b[1] - b[s], b[1]) + v.se);
	cout << ans << endl;
	return 0;
}


