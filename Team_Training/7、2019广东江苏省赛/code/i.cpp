#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int P = 1e9 + 7;
const int N = 5010;
int tmp[N], siz[N], u, v, n, m, k, x, f[N][N], ans, s1[N];
vi g[N];
int add(int a, int b) { a += b; return a >= P ? a - P : a;} 
int mul(int a, int b) { return 1ll * a * b % P;}

void dfs(int u, int fa) {
	siz[u] = 1;
	for (auto v : g[u]) {
		if (v == fa) continue;
		dfs(v, u);
		siz[u] += siz[v];
		
		rep(i, 0, siz[u] + 1) tmp[i] = f[u][i];
		rep(i, 0, siz[v] + 1) tmp[i + 1] = add(tmp[i+1], f[v][i]);

		s1[0] = f[u][0]; rep(i, 1, siz[u] + 1) s1[i] = add(s1[i-1], f[u][i]);
		rep(x, 0, siz[v] + 1) {
			if (k - x - 1 < 0) break;
			int  p = min(k - x - 1, x + 1);
			if (p > siz[u]) p = siz[u]; 
			tmp[x + 1] = add(tmp[x + 1], mul(f[v][x], s1[p]));
		}

		s1[0] = f[v][0]; rep(i, 1, siz[v] + 1) s1[i] = add(s1[i-1], f[v][i]);
		rep(y, 2, siz[u] + 1) {
			if (k - y - 1 < 0) break;
			int  p = min(k - y - 1, y - 2);
			if (p > siz[v]) p = siz[v]; 
			tmp[y] = add(tmp[y], mul(f[u][y], s1[p]));
		}
		rep(i, 0, siz[u]+1) f[u][i] = tmp[i];
	}
} 

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while (cin >> n >> m >> k) {
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, n+1) rep(j, 0, n+1) f[i][j] = 0;
		rep(i, 1, n) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		rep(i, 1, m+1) cin >> x, f[x][0] = 1;
		dfs(1, 0);
		ans = 0;
		rep(i, 0, n+1) ans = add(ans, f[1][i]);
		cout << ans << endl;
	}
	return 0;
}
