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

const int N = 1e5 + 7;
vi g[N];
int n, x, f[N];

void dfs(int u) {
	if (sz(g[u]) == 0) f[u] = 2;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		dfs(v);
		f[u] += max(f[v] - 1, 0);
	}
}

void dfs2(int u) {
	if (sz(g[u]) == 0) {
		cout << u << endl;
		exit(0);
	}
	int pos = g[u][0];
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if (f[v] > 1) pos = v; 
	}
	dfs2(pos);
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 2, n+1) cin >> x, g[x].pb(i);
	dfs(1);
	if (f[1] <= 1) {
		cout << "FIRST" << endl;
		dfs2(1);
	}else {
		cout << "SECOND" << endl;
	}
	return 0;
}
