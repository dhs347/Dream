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
#define endl '\n'
#define pw(c) (1ll<<(c))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef __int128 ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const ll inf = (ll)pw(60) * pw(60);

template<class U, class V> 
struct ZKW {
	static const int N = 1010, M = 400404;

	int h[N], ing[N], v[N], to[M], ne[M], e, s, t, n;
	U cap[M]; V dis[N], cost[M];
	void ini(int _n = N) {
		fill(h, h + (n = _n), -1); e = 0;
	}
	void liu(int u, int v, U c, V w) {
		to[e] = v; ne[e] = h[u]; cap[e] = c; cost[e] = w; h[u] = e++;
	}
	void link(int u, int v, U c, V w) {
		liu(u, v, c, w); liu(v, u, 0, -w);
	}
	void spfa() {
		queue<int> Q;
		fill(dis, dis + n, inf);
		ing[t] = true, dis[t] = 0;
		Q.push(t);
		while(!Q.empty()) {
			int c = Q.front(); Q.pop(); ing[c] = false;
			for(int k = h[c]; ~k; k = ne[k]) {
				int v = to[k];
				if(cap[k ^ 1] <= 0) continue;
				if(dis[c] + cost[k ^ 1] < dis[v]) {
					dis[v] = dis[c] + cost[k ^ 1];
					if(!ing[v]) Q.push(v), ing[v] = 1;
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
		if(c == t) return flow += mx, mincost += mx * dis[s], mx;
		v[c] = 1; U ret = 0;
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
		do do memset(v, 0, sizeof(v[0]) * n);
		while(dfs(s, inf));
		while(modlable());
		return mp(flow, mincost);
	}
};


ZKW<ll, ll> G;
const int N = 500;

int  n, m, s, t;
long long  sum, len, w;
ll a[N];
string ss;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	int x;
	rep(i, 1, n+1) cin >> x, a[i] = x; //cin >> a[i];
	a[0]=-inf/2; per(i, 1, n+1) a[i] -= a[i-1];
	a[++n] = inf/2;
	G.ini(n + 10); s = G.n - 5; t = s + 1;
	rep(i, 1, m+1) {
		cin >> ss >> len >> w;
		rep(j, 1, n+1) {
			int k = j + len;
			if (k > n) break;
			if (ss == "+") G.link(k, j, inf, w);
			else G.link(j, k, inf, w);
		}
	}
	rep(i, 1, n+1) if (a[i] > 0) G.link(s, i, a[i], 0);else G.link(i, t, -a[i], 0), sum += -a[i];
	auto ans = G.run(s, t);
	//de(sum);
	//de(ans.fi);
	if (ans.fi != sum) {
		cout << -1 << endl;
	}else {
		vi tmp;
		while (ans.se) {
			tmp.pb(ans.se % 10);
			ans.se /= 10;
		}
		if (!sz(tmp)) tmp.pb(0);
		per(i, 0, sz(tmp)) cout << tmp[i];
		cout << endl;
	}
	return 0;
}

