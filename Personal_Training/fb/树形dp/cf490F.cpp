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

const int N = 6005;
vi V, g[N];
int a[N], n, u, v, ans;
short f[N][N], h[N][N];
void dfs(int u, int fa) {
	f[u][a[u]] = h[u][a[u]] = 1;
	per(i, 0, n+1) f[u][i] = max(f[u][i+1], f[u][i]);
	rep(i, 1, n+1) h[u][i] = max(h[u][i], h[u][i-1]);
	for (auto v: g[u]) if (v != fa) {
		dfs(v, u);
		rep(i, 1, n+1) ans = max(ans, f[v][i] + h[u][i-1]);
		rep(i, 0, n+1) ans = max(ans, h[v][i] + f[u][i+1]);
		f[u][a[u]] = max(f[u][a[u]], (short)(f[v][a[u]+1] + 1));
		h[u][a[u]] = max(h[u][a[u]], (short)(h[v][a[u]-1] + 1));
		per(i, 0, n+1) f[u][i] = max(f[u][i], f[v][i]), f[u][i] = max(f[u][i+1], f[u][i]);
		rep(i, 1, n+1) h[u][i] = max(h[u][i], h[v][i]), h[u][i] = max(h[u][i], h[u][i-1]);
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n+1) cin >> a[i], V.pb(a[i]);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 1, n+1) a[i] = lower_bound(all(V), a[i]) - V.begin(), a[i]++;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	ans = 1;
	dfs(1, 0);
	cout << ans << endl;
	return 0;
}


