#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl '\n'
#define pw(x) (1ll <<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 505050;

int n, m, deg[N], pre[N];
bool del[N], vis[N];
int du[N];
vi g[N], ng[N], ans;

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	int fx = find(x), fy = find(y);
	if(fx == fy) return ;
	ng[x].pb(y), ng[y].pb(x);
//	dd(x), dd(du[x]), dd(y), de(du[y]);
	++du[x], ++du[y];
//	dd(x), dd(du[x]), dd(y), de(du[y]);
	pre[fx] = fy;
}
void dfs(int u) {
	ans.pb(u); vis[u] = 1;
	for(auto v : ng[u]) if(!vis[v]) {
		dfs(v);
	}
}
map<pii, bool> ee;
int main() {
	//freopen("drawing.in", "r", stdin);
	//freopen("drawing.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
		++deg[u], ++deg[v];
		ee[mp(u, v)] = ee[mp(v, u)] = 1;
	}
	priority_queue<pii> que;
	rep(i, 1, n + 1) pre[i] = i;
	rep(i, 1, n + 1) que.push(mp(-deg[i], i));
	while(!que.empty()) {
		auto u = que.top(); que.pop();
		if(del[u.se]) continue;
		del[u.se] = 1;
		int uu = 0, vv = 0;
		for(auto v : g[u.se]) if(!del[v]) {
			if(uu == 0) uu = v;
			else vv = v;
		}
	//	dd(u.se), dd(uu), de(vv);
		if(uu && vv) {
		if(ee[mp(uu, vv)]) {
			--deg[uu];
			--deg[vv];
			que.push(mp(-deg[uu], uu));
			que.push(mp(-deg[vv], vv));
			join(u.se, uu);
			join(u.se, vv);
		} else {
			g[uu].pb(vv);
			g[vv].pb(uu);
			ee[mp(uu, vv)] = ee[mp(vv, uu)] = 1;
			join(u.se, uu);
			join(u.se, vv);
		}
		}
	}
	int u = 0, v = 0;
//	rep(i, 1, n + 1) dd(i), de(du[i]);
	rep(i, 1, n + 1) if(du[i] == 1) {
		if(u == 0) u = i;
		else v = i;
	}
	ng[u].pb(v), ng[v].pb(u);
	rep(i, 1, n + 1) sort(all(ng[i]));
	dfs(1);
	assert(sz(ans) == n);
	rep(i, 0, sz(ans)) cout << ans[i] << " \n"[i == sz(ans) - 1];
	return 0;
}
