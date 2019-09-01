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
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 355;
vector<pair<int, ll> > g[N];
const ll inf = pw(60);

int T, n, m, u, v;
ll w, dis[N];
int vis[N];
queue<int> q;

ll spfa(int u, int v) {
	rep(i, 1, n+1) dis[i] = inf;
	dis[u] = 0; vis[u] = 1; q.push(u);
	while (!q.empty()) {
		u = q.front(); q.pop(); vis[u] = 0;
		for (auto c : g[u]) if (dis[u] + c.se < dis[c.fi]){
			dis[c.fi] = dis[u] + c.se;
			if (!vis[c.fi]) {
				vis[c.fi] = 1; q.push(c.fi);
			}
		}
	}
	return -dis[v];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, m+1) {
			cin >> u >> v >> w;
			u++; v++;
			g[u].pb(mp(v, w));
		}
		rep(i, 0, 6) {
			cin >> u >> v;
			u++; v++;
			w = spfa(v, u);
			cout << w << endl;
			g[u].pb(mp(v, w));
		}
	}
	return 0;
}
