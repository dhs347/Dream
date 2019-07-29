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
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 2005;
int n, a[N], K, s, t, T;

const int inf = 1e9 + 8;

template<class U, class V> 
struct ZKW{
	static const int N = 5005, M = 4e6 + 1e5;
	int h[N], ing[N], v[N], to[M], ne[M], e, s, t, n;
	U cap[M]; V dis[N], cost[M];
	void ini(int _n = N) {fill(h, h + (n = _n), -1); e = 0;}
	void liu(int u, int v, U c, V w) { to[e] = v;ne[e] = h[u]; cap[e] = c;cost[e] = w;h[u] = e++;}
	void link(int u, int v, U c, V w) { liu(u, v, c, w); liu(v, u, 0, -w);}
	void spfa() {
		queue<int> Q;
		fill(dis, dis+n, inf);
		ing[t] = 1, dis[t] = 0; Q.push(t);
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
		rep(c, 0, n) if(v[c]) {
			for(int k = h[c]; ~k; k = ne[k]) {
				int t = to[k];
				if(!v[t] && cap[k] > 0) {
					Min = min(Min, dis[t] + cost[k] - dis[c]);
				}
			}
		}
		if(Min == inf) return 0;
		rep(i, 0, n) if(v[i]) dis[i] += Min;
		return 1;
	}
	U dfs(int c, U mx) {
		if(c == t) {
			return flow += mx, mincost += mx * dis[s], mx;
		}
		v[c] = true; U ret = 0;
		for(int k = h[c]; ~k; k = ne[k]) {
			int t = to[k];
			if(!v[t] && cap[k] > 0 && dis[c] - cost[k] == dis[t]) {
				U tmp = dfs(t, min(cap[k], mx - ret));
				cap[k] -= tmp, cap[k ^ 1] += tmp;
				ret += tmp;
				if(ret == mx) return ret;
			}
		}
		return ret;
	}
	pair<U, V> run(int _s, int _t) {
		s = _s, t = _t;
		spfa();
		flow = mincost = 0;
		do {
			//de(flow);de(mincost);
				do memset(v, 0, sizeof(v[0]) * n);
			  while (dfs(s, K - flow));
			  if (flow == K) return mp(flow, mincost);
			}
		while(modlable());
		return mp(flow, mincost);
	}
};


ZKW<int, int> G;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	//de(pow(1e5, 5/3.0) / 10);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> K;
		n = 500; K = 10;
		rep(i, 1, n+1) a[i] = rand() % 100000;//cin >> a[i];
		G.ini(n * 2 + 10); s = G.n - 5; t = s + 1;
		rep(i, 1, n+1) G.link(i, i + n, 1, -a[i]), G.link(s, i, 1, 0), G.link(i + n, t, 1, 0);
		rep(i, 1, n+1) rep(j, i+1, n+1) if (a[i] <= a[j]) G.link(i + n, j, 1, 0);
		pii ans = G.run(s, t);
		cout << -ans.se << endl;
	}
	return 0; 
}
