#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(a) cout << #a << " = " << a << " " 
#define de(a) cout << #a << " = " << a << endl
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 303030;

int n, m;
int in[N], out[N];
int dp[N];
pii rng[N];
vi g[N], ng[N];
vi ans;

bool solve() {
	// q1: dp min, id
	// q2: L min, id
	priority_queue<pii> q1, q2;
	rep(i, 1, n + 1) if(in[i] == 0) q2.push(mp(-rng[i].fi, i));
	rep(i, 1, n + 1) {
		while(!q2.empty()) {
			auto u = q2.top(); 
			if(-u.fi <= i) {
				q2.pop();
				u.fi = -dp[u.se];
				q1.push(u);
			} else {
				break;
			}
		}
		if(q1.empty() || rng[q1.top().se].se < i) return 0;
		auto u = q1.top(); q1.pop();
		ans.pb(u.se);
		for(auto v : g[u.se]) {
			--in[v];
			if(in[v] == 0) q2.push(mp(-rng[v].fi, v));
		}
	}
	return 1;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> rng[i].fi >> rng[i].se;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		++out[u]; ++in[v];
		g[u].pb(v);
		ng[v].pb(u);
	}
	rep(i, 1, n + 1) dp[i] = rng[i].se;
	vi que;
	rep(i, 1, n + 1) if(out[i] == 0) que.pb(i);
	rep(i, 0, sz(que)) {
		int u = que[i];
		for(auto v : ng[u]) {
			--out[v];
			dp[v] = min(dp[v], dp[u]);
			if(out[v] == 0) que.pb(v);
		}
	}
	rep(i, 1, n + 1) out[i] = sz(g[i]);
	if(solve()) {
		for(auto u : ans) cout << u << endl;
	} else {
		cout << -1 << endl;
	}
	return 0;
}
