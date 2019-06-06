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

const int N = 30303;

int n, m, k, r1, tim;
int dis[N], sz[N], f1[N], vv[N], f2[N];
ll r2;
bool vis[N];
vector<pii> vec;
vector<pii> g[N], G[N];

void dij() {
	memset(dis, 0x3f, sizeof(dis));
	priority_queue<pii> que;
	dis[1] = 0;
	que.push(mp(0, 1));
	while(!que.empty()) {
		pii t = que.top(); que.pop();
		int u = t.se;
		if(-t.fi != dis[u]) continue;
		rep(i, 0, sz(g[u])) {
			int v = g[u][i].fi;
			int c = dis[u] + g[u][i].se;
			if(dis[v] > c) {
				dis[v] = c;
				que.push(mp(-c, v));
			}
		}
	}
}

void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	rep(i, 0, sz(G[c])) {
		int t = G[c][i].fi;
		if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
		if(!rt && sz[c] * 2 > Sz) rt = c;
	}
}
void gao(int c, int len) {
	if(vv[c] != tim) {
		vv[c] = tim;
		f1[c] = len;
		f2[c] = 1;
	} else {
		if(f1[c] == len) {
			++f2[c];
		} else if(len > f1[c]) {
			f1[c] = len;
			f2[c] = 1;
		}
	}
}
void dfs(int u, int fa, int c, int len) {
	vec.pb(mp(c, len));
	if(c < k && vv[k - c] == tim) {
		int t = len + f1[k - c];
		if(t > r1) {
			r1 = t;
			r2 = 1;
		} else if(t == r1) {
			r2 += f2[k - c];
		}
	}
	rep(i, 0, sz(G[u])) {
		int v = G[u][i].fi;
		if(!vis[v] && v != fa) dfs(v, u, c + 1, len + G[u][i].se);
	}
}
void dfs(int c) {
	int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
	++tim;
	gao(1, 0);
	rep(i, 0, sz(G[rt])) {
		int v = G[rt][i].fi;
		if(!vis[v]) {
			vec.clear();
			dfs(v, rt, 1, G[rt][i].se);
			rep(j, 0, sz(vec)) {
				gao(vec[j].fi + 1, vec[j].se);
			}
		}
	}
	rep(i, 0, sz(G[rt])) {
		int t = G[rt][i].fi;
		if(!vis[t]) dfs(t);
	}
}
void dfs0(int u) {
	vis[u] = 1;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi;
		if(dis[u] + g[u][i].se == dis[v] && !vis[v]) {
			G[u].pb(g[u][i]);
			G[v].pb(mp(u, g[u][i].se));
			dfs0(v);
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> k;
	rep(i, 1, m + 1) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	rep(i, 1, n + 1) sort(all(g[i]));
	dij();
	dfs0(1);
	memset(vis, 0, sizeof(vis));
	dfs(1);
	cout << r1 << " " << r2 << endl;
	return 0;
}
