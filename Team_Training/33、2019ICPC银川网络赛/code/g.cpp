#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1e5 + 7;
const ll inf = pw(60);
ll f[N][105];
vector<pii> g[N];
int u, v, w, T, n, k, root, siz[N];
ll tmp[N];

inline bool cmp(const pii &a, const pii &b) {
	return siz[a.fi] < siz[b.fi];
}

inline void dfs(int u, int fa) {
	if (sz(g[u]) == 1) {
		siz[u] = 1; f[u][1] = 0;
	}else siz[u] = 0;

	for (auto  v : g[u]) if (v.fi != fa) {
		dfs(v.fi, u);
		int t1 = min(siz[u], k);
		int t2 = min(siz[v.fi], k);
		int t4 = min(t1 + t2, k);
		rep(i, 0, t4+1) tmp[i] = f[u][i];
		rep(i, 1, t2+1) {
			int t3 = min(t1, t4 - i);
			ll w = i * (k - i) * v.se + f[v.fi][i];
			rep(j, 0, t3+1) if (tmp[i+j] > w + f[u][j]) tmp[i+j] = f[u][j] + w;
		}
		siz[u] += siz[v.fi];
		rep(i, 0, t4+1) f[u][i] = tmp[i];
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	srand(time(0));
	rep(cas, 0, T) {
		cin >> n >> k;
		//n = 100000; k = 100;
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, n+1) rep(j, 1, k+1) f[i][j] = inf;
		rep(i, 1, n) {
			cin >> u >> v >> w;
			//u = i + 1;
			//if (u <= n - k) v = rand() % i + 1;
			//else v = n - k;
			//v = 1;
			//w = rand() % 100000;
			g[u].pb(mp(v, w));
			g[v].pb(mp(u, w));
		}
		root = 1;
		rep(i, 1, n+1) if (sz(g[i]) > 1) {
			root = i;
		} 
		cout << "Case #" << cas + 1 << ": ";
		if (n == 1) {
			cout << 0 << endl;
			continue;
		}
		if (n == 2 && k == 1) {
			cout << 0 << endl;
			continue;
		}
		if (n == 2 && k == 2) {
			cout << w << endl;
			continue;
		}
		dfs(root, 0); 
		cout << f[root][k] << endl;
	}
	return 0;
}
