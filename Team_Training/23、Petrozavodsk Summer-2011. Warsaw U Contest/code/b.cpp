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
#define sz(x) ((int)x.size())
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const ll inf = pw(50);

vi an[1000];

template<class U, class V> 
struct ZKW{
	static const int N = 2004, M = 1011010;
	int h[N], ing[N], v[N], to[M], ne[M], e, s, t, n;
	U cap[M]; V dis[N], cost[M];
	void ini(int _n = N) {fill(h, h+(n = _n), -1); e = 0;}
	void liu(int u, int v, U c, V w) {
		to[e] = v; ne[e] = h[u]; cap[e] = c; cost[e] = w; h[u] = e++;
	}
	void link(int u, int v, U c, V w) {
		liu(u, v, c, w);
		liu(v, u, 0, -w);
	}
	void spfa() {
		queue<int> Q;
		fill(dis, dis+n, inf);
		ing[t] = 1; dis[t] = 0;
		Q.push(t);
		while (!Q.empty()) {
			int c = Q.front(); Q.pop(); ing[c] = 0;
			for (int k = h[c]; ~k; k = ne[k]) {
				int v = to[k];
				if (cap[k ^ 1] <= 0) continue;
				if (dis[c] + cost[k ^ 1] < dis[v]) {
					dis[v] = dis[c] + cost[k ^ 1];
					if (!ing[v]) Q.push(v), ing[v] = 1;
				}
			}
		}
	}
	U flow; V mincost;
	bool modlable() {
		V Min = inf;
		rep(c, 0, n) if (v[c]) 
			for (int k = h[c]; ~k; k = ne[k]) {
				int t = to[k];
				if (!v[t] && cap[k] > 0) 
					Min = min(Min, dis[t] + cost[k] - dis[c]);
			}
			if (Min == inf)  return 0;
			rep(i, 0, n) if (v[i]) dis[i] += Min;
			return 1;
	}
	U dfs(int c, U mx) {
		if (c == t) return flow += mx, mincost += mx * dis[s], mx;
		v[c] = 1; U ret = 0;
		for (int k = h[c]; ~k; k= ne[k]) {
			int t = to[k];
			if (!v[t] && cap[k] > 0 && dis[c] - cost[k] == dis[t]) {
				U tmp = dfs(t, min(cap[k], mx - ret));
				cap[k] -= tmp; cap[k ^ 1] += tmp;
				ret += tmp;
				if (ret == mx) return ret;
			} 
		}
		return ret;
	}
	pair<U, V> run(int _s, int _t) {
		s = _s; t = _t;
		flow = mincost = 0;
		spfa();
		do do memset(v, 0, sizeof(v[0]) * n);
			while (dfs(s, inf));
		while (modlable());
		for (int i = 0; i < e; i += 2) {
			int u = to[i ^ 1], v = to[i];
			if (u != s && v != t && cap[i] == 0) {
				an[u].pb(v);
			}
		}
		return mp(flow, mincost);
	}
};

ZKW<ll, ll> G;

const int N = 3005;
int n, m, r, t, k, now, u, v, cnt[N], S, T;

int main() {
	freopen("contest.in", "r", stdin);
	freopen("contest.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> r >> t >> k;
	G.ini(n + m + 10); S = G.n - 5; T = S + 1;
	rep(i, 1, k+1) {
		cin >> u >> v;
		G.link(u, v + n, 1, 0);
		cnt[u]++;
	}
	rep(i, 1, n+1) {
		now = 0;
		rep(j, 0, cnt[i]) {
			now += r;
			if (now > t) break;
			G.link(S, i, 1, now);
		}
	}
//	return 0;
	rep(i, 1, m+1) G.link(i + n, T, 1, 0);
	auto ans = G.run(S, T);
	cout << ans.fi << " " << ans.se << endl;
	rep(i, 1, n+1) {
		now = 0;
		for (auto u : an[i]) {
			cout << i << " " << u - n << " " << now << endl;
			now += r;
		}
	}	
	return 0;
}
