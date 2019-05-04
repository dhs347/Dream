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

const int N = 101010;

int n;
vi g[N];
int vis[N];
vi ans;
bool f;

void dfs(int u) {
	if(f) return ;
	ans.pb(u);
	vis[u] = 1;
	if(sz(ans) == n) {
		de(n);
		rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == n - 1];
		f = 1;
		return ;
	}
	for(auto v : g[u]) if(!vis[v]) dfs(v);
	vis[u] = 0;
	ans.pop_back();
}

void solve() {
	ans.clear();
	f = 0;
	rep(i, 1, n + 1) g[i].clear(), vis[i] = 0;
	rep(i, 2, n + 1) g[i].pb(i - 1);
	rep(i, 1, n + 1) {
		if(i * 2 <= n) g[i].pb(i * 2);
		if(i * 2 + 1 <= n) g[i].pb(i * 2 + 1);
	}
	rep(i, 2, n + 1) g[i].pb(i / 2);
	dfs(1);
}

int main() {
//	std::ios::sync_with_stdio(0);
//	std::cin.tie(0);
	rep(i, 1, 1e5 + 1) n = i, solve();
	return 0;
}
