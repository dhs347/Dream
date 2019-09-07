#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 7;
const int P = 1e9 + 7;

int f[N], dep[N], n, u, v, inv[N];
vi g[N];

int kpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) res = 1ll * res * a % P;
		a = 1ll * a * a % P;
		b >>= 1;
	}
	return res;
}

void dfs(int u, int fa) {
	for (auto v : g[u]) if (v != fa) {
		dfs(v, u);
		dep[u] = max(dep[u], dep[v]);
	} 
	dep[u]++;
}

void dfs2(int u, int fa) {
	if (dep[u] == 1) {
		f[u] = 0;
		return;
	}
	int now = 0, cnt = 0;
	for (auto v : g[u]) if (v != fa) {
		cnt++;
		if (dep[v] + 1 == dep[u]) dfs2(v, u);
		else f[v] = 1;
		now = (now + f[v]) % P;
	}
	now = 1ll * now * inv[cnt] % P;
	now = kpow(now, cnt);
	f[u] = now;

}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	inv[0] = inv[1] = 1;
	rep(i, 2, n+1) inv[i] = 1ll * (P - P / i) * inv[P % i] % P;
	//de(1ll * 1 * inv[3] % P);
	dfs(1, 0);
	dfs2(1, 0);
	cout << (1 - f[1] + P) % P;
	return 0;
}
