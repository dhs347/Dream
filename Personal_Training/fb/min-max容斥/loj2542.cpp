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

const int N = 30;
int a[N], b[N], f[1 << 18], ans, inv[N];
bool vis[N];
vi g[N];
int n, q, x, u, v, S, k, now;
void dfs(int u, int fa) {
	a[u] = b[u] = 0;
	if (vis[u]) return;
	a[u] = inv[sz(g[u])]; b[u] = 1;
	int t = 0;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if (v == fa) continue; 
		dfs(v, u);
		t = add(t, mul(inv[sz(g[u])], a[v]));
		b[u] = add(b[u], mul(inv[sz(g[u])], b[v]));
	}
	t = kpow(add(1, -t), P - 2);
	a[u] = mul(a[u], t);
	b[u] = mul(b[u], t);
	//a[u] /= 1 - t;
	//b[u] /= 1 - t;
}


int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> q >> x;
	inv[1] = 1; rep(i, 2, n+1) inv[i] = mul(P - P / i, inv[P % i]);
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	} 
	S = pw(n) - 1;
	rep(i, 1, S+1) {
		rep(j, 1, n+1) if (pw(j - 1) & i) vis[j] = 1;else vis[j] = 0;
		dfs(x, 0); 
		f[i] = b[x];
	}
	
	rep(cas, 0, q) {
		cin >> k;
		now = 0; ans = 0;
		rep(i, 0, k) cin >> u, now |= pw(u - 1);
		for (int x = now; x > 0; x = (x - 1) & now) {
			int t = __builtin_popcount(x);
			if (t & 1) ans = add(ans, f[x]);else ans = add(ans, -f[x]);
		}
		cout << ans << endl;
	}
	return 0;
}


