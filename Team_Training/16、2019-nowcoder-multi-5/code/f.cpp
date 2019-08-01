#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int inf = 1e9 + 7;

template<class T>
struct Dinic {
	const static int N = 10101, M = 5e6;
	int s, t, n, h[N], cur[N], level[N], q[N], e, ne[M], to[M];
	T cap[M], flow;
	void liu(int u, int v, T w) {
		to[e] = v; ne[e] = h[u];
		cap[e] = w; h[u] = e++;
	}
	void link(int u, int v, T w) {
		liu(u, v, w);
		liu(v, u, 0);
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
				if(!mx) return ret;
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
			flow += dfs(s, ~0U>>1);
		}
		return flow;
	}
};

Dinic<int> G;
const int N = 1e4+ 6;
int n, a[N], vis[N], use[N], m, col[N], s, t, link[N];
vi g[N];
void dfs(int u) {
	vis[u] = 1; 
	for (auto v : g[u]) {
		if (!vis[v]) {
			col[v] = col[u] ^ 1;
			dfs(v);
		}else assert(col[v] != col[u]);
	}
}

void MVC(int n, vi g[]) {
	fill_n(vis, n+1, 0);
	fill_n(use, n+1, 0);
	queue<int> Q;
	per(i, 1, n+1) link[link[i]] = i;
	rep(i, 1, n+1) if (!link[i]) vis[i] = use[i] = 1, Q.push(i);
	while (!Q.empty()) {
		int u = Q.front(); Q.pop();
		if (use[u] == 1) {
			for(auto v : g[u]) {
				use[v] = 2;
				if (!vis[v]) vis[v] = 1, Q.push(v);
			}
		}else {
			int v = link[u];
			use[v] = 1;
			if (!vis[v]) vis[v] = 1, Q.push(v);
		}
	}
	rep(i, 1, n+1) if (link[i] && !use[link[i]] && col[i] == 0) use[i] = 2;
	return;
} 

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n+1) {
		cin >> a[i];
	}
	G.ini(n + 10), s = G.n - 5; t = s + 1;
	rep(i, 1, n+1) rep(j, i+1, n+1) {
		if (__builtin_popcount(a[i] ^ a[j]) <= 1) {
			g[i].pb(j);
			g[j].pb(i);
		} 
	}
	rep(i, 1, n+1) if (!vis[i]) dfs(i);
	rep(i, 1, n+1) if (col[i] == 0) {
		G.link(s, i, 1);
		for (auto v : g[i]) G.link(i, v, 1);
	}else G.link(i, t, 1);
	m = n - G.run(s, t);
	for (int e = 0; e < G.e; e += 2) if (G.cap[e] == 0){
		int u = G.to[e ^ 1], v = G.to[e];
		if (u != s && v != t) link[u] = v, link[v] = u;//, dd(u), de(v); 
	}
//	rep(i, 1, n+1) de(link[i]);
	MVC(n, g);
/*&	rep(i, 1, n+1) {
		dd(i);de(col[i]);
		for (auto u : g[i]) cout << u << " ";
		cout << endl;
	}*/

	cout << m << endl;
	rep(i, 1, n+1) if (use[i] != 2) {
		m--;
		cout << a[i] << " \n"[m == 0];
	}
	return 0;
}
