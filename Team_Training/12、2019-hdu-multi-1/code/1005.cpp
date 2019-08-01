#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 10101;

int n, m;
vector<pii> g[N];
ll dis[N];

template<class T>
struct Dinic {
	const static int N = 10101, M = N * 10;
	int s, t, n, h[N], cur[N], level[N], q[N], e, ne[M], to[M];
	T cap[M], flow;
	void liu(int u, int v, T w) {
		to[e] = v; ne[e] = h[u]; cap[e] = w; h[u] = e++;
	}
	void link(int u, int v, T w) {
		liu(u, v, w); liu(v, u, 0);
	}
	void ini(int _n = N) {
		fill(h, h + (n = _n), -1); e = 0;
	}
	bool bfs() {
		int L = 0, R = 0;
		fill(level, level + n, -1);
		level[q[R++] = s] = 0;
		while(L < R && level[t] == -1) {
			int c = q[L++];
			for(int k = h[c]; ~k; k = ne[k]) {
				if(cap[k] > 0 && level[to[k]] == -1) {
					level[q[R++] = to[k]] = level[c] + 1;
				}
			}
		}
		return ~level[t];
	}
	T dfs(int c, T mx) {
		if(c == t) return mx;
		T ret = 0;
		for(int &k = cur[c]; ~k; k = ne[k]) {
			if(level[to[k]] == level[c] + 1 && cap[k] > 0) {
				T flow = dfs(to[k], min(mx, cap[k]));
				ret += flow; cap[k] -= flow, cap[k ^ 1] += flow; mx -= flow;
			}
		}
		level[c] = -1;
		return ret;
	}
	T run(int _s, int _t) {
		s = _s, t = _t;
		flow = 0; 
		while(bfs()) {
			copy(h, h + n, cur);
			flow += dfs(s, pw(60));
		}
		return flow;
	}
};

Dinic<ll> G;

void dij() {
	priority_queue<pair<ll, int> > que;
	rep(i, 2, n + 1) dis[i] = 1e18;
	que.push(mp(0, 1));
	while(!que.empty()) {
		auto u = que.top(); que.pop();
		if(-u.fi != dis[u.se]) continue;
		for(auto v : g[u.se]) {
			ll t = dis[u.se] + v.se;
			if(dis[v.fi] > t) {
				dis[v.fi] = t;
				que.push(mp(-t, v.fi));
			}
		}
	}
}

void solve() {
	cin >> n >> m;
	rep(i, 1, n + 1) g[i].clear();
	rep(i, 1, m + 1) {
		int u, v, w; cin >> u >> v >> w;
		g[u].pb(mp(v, w));
	}
	dij();
	G.ini(n + 3);
	rep(i, 1, n+1) {
		for (auto u : g[i]) {
			if (dis[i] + u.se == dis[u.fi]) G.link(i, u.fi, u.se);
		}
	}
	cout << G.run(1, n) << endl;
//	rep(i, 1, n + 1) dd(i), de(dis[i]);
}

int main() {
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
