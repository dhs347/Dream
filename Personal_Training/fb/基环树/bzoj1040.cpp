// 求基环树带权最大点独立集，注意自环和二元环时的重边 
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
int a[N], ok, p1, p2, u, v, n;
ll dp[N][2], ans, tmp;
int vis[N], vis2[N], tim;
vi g[N];
void dfs(int u, int fa) {
	vis[u] = ++tim;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if (v == fa) continue;
		if (vis[v] && vis[v] < vis[u]) {
			ok = 1; p1 = u; p2 = v;
			continue;
		}
		if (!vis[v]) dfs(v, u);
	}
}

void dfs2(int u) {
	vis2[u] = 1;
	dp[u][0] = 0;
	dp[u][1] = a[u];
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if ((u == p1 && v == p2) || (u == p2 && v == p1) || vis2[v]) continue;
		dfs2(v);
		dp[u][0] += max(dp[v][0], dp[v][1]);
		dp[u][1] += dp[v][0];
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
		cin >> a[i] >> u;
		g[i].pb(u);
		g[u].pb(i);
	}
	rep(i, 1, n+1) if (!vis[i]) {
		ok = 0;
		dfs(i, 0);
		if (!ok) {
			dfs2(i);
			ans += max(dp[i][0], dp[i][1]);
		}else { 
			rep(i, 1, n+1) vis2[i] = 0;
			dfs2(p1);
			tmp = dp[p1][0];
			rep(i, 1, n+1) vis2[i] = 0;
			dfs2(p2);
			ans += max(tmp, dp[p2][0]);
		}
	}
	cout << ans << endl;
	return 0;
}


