#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 2e5 + 78;
int ans, fa[N], u, v, n, m, d[N], ok[N];
vi g[N];

int get(int x){
	if (x == fa[x]) return x;
	int t = fa[x];
	fa[x] = get(fa[x]);
	d[x] ^= d[t];
	return fa[x];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, 2*m+1) {
		cin >> u >> v;
		g[v].pb(u);
	}
	rep(i, 1, n+1) fa[i] = i; 
	rep(i, 1, m+1) {
		u = g[i][0]; v = g[i][1];
		u = get(u); v = get(v);
		if (u != v) {
			fa[u] = v;
			d[u] = 1;
			ok[v] |= ok[u];
		}else {
			if ((d[g[i][0]] ^ d[g[i][1]] ^ 1) == 1) ok[u] = 1;
		}
	}
	ans = n;
	rep(i, 1, n+1) if (get(i) == i && !ok[i]) ans--;
	cout << ans << endl;
	return 0;
}
