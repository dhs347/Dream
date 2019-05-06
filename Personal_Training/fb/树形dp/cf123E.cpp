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

const int N = 1e5 + 7;
int siz[N], x[N], y[N], sx, sy, n, u, v;
db f[N], h[N], ans;
vi g[N];
void dfs1(int u, int fa) {
	siz[u] = 1;
	for (auto v : g[u]) if (v != fa) {
		dfs1(v, u);
		siz[u] += siz[v];
		f[u] += f[v];
	}
	f[u] += siz[u] * 1.0 * y[u] / sy;
}

void dfs2(int u, int fa, db w) {
	h[u] = f[u] + w + (n - siz[u]) * 1.0 * y[u] / sy;
	ans += (n - h[u]) * 1.0 * x[u] / sx;
	for (auto v : g[u]) if (v != fa) {
		dfs2(v, u, h[u] - f[v] - siz[v] * 1.0 * y[u] / sy);
	}
}

int main() {
	freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(12);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i, 1, n+1) cin >> x[i] >> y[i], sx += x[i], sy += y[i];
	dfs1(1, 0);
	dfs2(1, 0, 0);
	cout << ans << endl;
	return 0;
}


