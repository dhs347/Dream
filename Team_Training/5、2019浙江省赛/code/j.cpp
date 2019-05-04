#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 1e6 + 7;
int T, u, v, n, m, ans, ne[N];
bool vis[N];
priority_queue<int,vi, greater<int> > q, q2;
vi g[N];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		fill_n(vis, n+1, 0);
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, m+1) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		ans = 0;
		rep(i, 1, n+1) if (!vis[i]) {
			ans++;vi tmp;
			q.push(i);vis[i] = 1;
			while (!q.empty()) {
				u = q.top(); q.pop();
				tmp.pb(u);
				rep(i, 0, sz(g[u])) {
					int v = g[u][i];
					if (vis[v]) continue;
					vis[v] = 1;
					q.push(v);
				}
			}
			rep(i, 0, sz(tmp) - 1) ne[tmp[i]] = tmp[i+1];
			ne[tmp.back()] = -1;
			q2.push(i);
		}
		cout << ans << endl;
		int cnt = 0;
		while (!q2.empty()) {
			u = q2.top(); q2.pop();
			cnt++; cout << u << " \n"[cnt == n];
			if (ne[u] != -1) q2.push(ne[u]);
		}
	}
	return 0;
}
