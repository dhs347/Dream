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
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 505;
bool f[N][2][N];
int ans[N], n, x, root;
vi g[N];

void dfs(int u) {
	if (sz(g[u]) == 0) {
		f[u][0][0] = f[u][1][1] = 1;
		return;
	}
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		dfs(v);
	}
	if (sz(g[u]) == 1) {
		int v = g[u][0];
		f[u][1][1] = f[v][0][0];
	}else {
		int v1 = g[u][0], v2 = g[u][1];
	//	de(f[v1][1][0]);
		rep(i, 0, n+1) f[u][0][i] = (f[v1][1][i] & f[v2][1][i]);
		rep(i, 1, n+1) 
			f[u][1][i] = ((f[v1][0][i-1] | f[v1][1][i-1]) & (f[v2][0][i-1] | f[v2][1][i-1]));
	}
}

void dfs2(int u, int o, int k) {
	ans[u] = o;
	if (sz(g[u]) == 1) {
		dfs2(g[u][0], 0, 0);
	}else if (sz(g[u]) == 2){	
		int v1 = g[u][0], v2 = g[u][1];
		if (o == 0) {
			dfs2(v1, 1, k);
			dfs2(v2, 1, k);
		}else {
			if (f[v1][0][k-1]) dfs2(v1, 0, k-1);
			else dfs2(v1, 1, k-1);
			if (f[v2][0][k-1]) dfs2(v2, 0, k-1);
			else dfs2(v2, 1, k-1);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> x;
		if (x == 0) root = i;else g[x].pb(i);
	}
	dfs(root);
	rep(i, 0, n+1) {
		rep(o, 0, 2) if (f[root][o][i]) {
			dfs2(root, o, i);
			rep(i, 1, n+1) cout << "RB"[ans[i]];
			cout << endl;
			return 0;
		}
	}
	cout << "Impossible" << endl;
	return 0;
}
