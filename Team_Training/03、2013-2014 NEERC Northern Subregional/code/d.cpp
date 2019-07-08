#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll << (x))
#define endl '\n'
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 10101;

int n, m;
int val[N];
bool vis[N];
vector<pii> g[N];
priority_queue<pii> que;

int main() {
	freopen("dwarf.in", "r", stdin);
	freopen("dwarf.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> val[i], que.push(mp(-val[i], i));
	rep(i, 1, m + 1) {
		int w, u, v;
		cin >> w >> u >> v;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	int cnt = 0;
	while(!que.empty() && cnt < n) {
		auto u = que.top(); que.pop();
		if(vis[u.se]) continue;
		vis[u.se] = 1;
		if(u.se == 1) {
			cout << val[u.se] << endl;
			return 0;
		}
		for(auto v : g[u.se]) {
			if(vis[v.fi] && val[v.se] > val[u.se] + val[v.fi]) {
				val[v.se] = val[u.se] + val[v.fi];
				que.push(mp(-val[v.se], v.se));
			}
		}
	}
	return 0;
}
