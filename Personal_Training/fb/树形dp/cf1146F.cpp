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
const int P = 998244353;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 2e5 + 7;
int f[N][2], n, u, dp[N], vis[N];
vi g[N];

void dfs(int u) {
	f[u][0] = 1; dp[u] = 1;
	if (!sz(g[u])) return;
	for (auto v : g[u]) {
		dfs(v);
		f[u][0] = mul(f[u][0], add(f[v][0], f[v][1]) + dp[v]);
	}
	int t = 1, cnt = 0;
	for (auto v : g[u]) if (dp[v]) t = mul(t, dp[v]);else cnt++;
	f[u][0] = add(f[u][0], cnt == 0 ? -t : 0);
	for (auto v : g[u]) {
		int x;
		if (cnt > 1) x = 0; 
		if (cnt == 1) {
			if (dp[v]) x = 0;else x = t;
		}
		if (cnt == 0) x = mul(t, kpow(dp[v], P - 2));
		f[u][1] = add(f[u][1], mul(x, f[v][0] + f[v][1]));
	}
	f[u][0] = add(f[u][0], -f[u][1]);
	for (auto v : g[u]) dp[u] = mul(dp[u], dp[v]);
	dp[u] = add(dp[u], f[u][0]);
}



int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 2, n+1) {
		cin >> u;
		g[u].pb(i); 
	}
	dfs(1);
	cout << dp[1];
	return 0;
}


