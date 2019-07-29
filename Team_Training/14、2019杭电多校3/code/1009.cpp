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
int n, a[N], K, s, t, T, dp[N];

const int inf = 1e9 + 8;

template<class U, class V> 
struct MCMF{
	static const int N = 5005, M = 4e6 + 1e5, MM = 3e5;
	int h[N], ing[N], pre[N], to[M], ne[M], e, s, t, n, Q[MM];
	U cap[M]; V dis[N], cost[M];
	void ini(int _n = N) {fill(h, h + (n = _n), -1); e = 0;}
	void liu(int u, int v, U c, V w) { to[e] = v;ne[e] = h[u]; cap[e] = c;cost[e] = w;h[u] = e++;}
	void link(int u, int v, U c, V w) { liu(u, v, c, w); liu(v, u, 0, -w);}
	bool spfa() {
		int l = 0, r = 1;
		fill(dis, dis+n, inf);
		ing[s] = 1, dis[s] = 0; Q[0] = s;
		while (l != r) {
			int c = Q[l]; l++; if (l >= MM) l -= MM; ing[c] = 0;
			for (int k = h[c]; ~k; k = ne[k]) if (cap[k] > 0){
				int v = to[k];
				if (dis[c] + cost[k] < dis[v]) {
					dis[v] = dis[c] + cost[k];
					pre[v] = k;
					if (!ing[v]) {
						Q[r++] = v, ing[v] = 1;
						if (r >= MM) r = 0;
					}
				}
			}
		}
		return dis[t] != inf;
	}
	U flow; V mincost;
	pair<U, V> run(int _s, int _t) {
		s = _s, t = _t;
		flow = mincost = 0;
		while (spfa()) {
			U pl = inf; int p, k;
			for (p = t; p != s; p = to[k ^ 1]) pl = min(pl, cap[k = pre[p]]);	
			pl = min(pl, K - flow);
			for (p = t; p != s; p = to[k ^ 1]) {
				k = pre[p];
				cap[k] -= pl;
				cap[k ^1] += pl;
			}
			mincost += pl * dis[t];
			flow += pl;
			if (flow == K) break;
		}
		return mp(flow, mincost);
	}
};


MCMF<int, int> G;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> K;
		rep(i, 1, n+1) cin >> a[i];
		G.ini(n * 2 + 10); s = G.n - 5; t = s + 1;
		rep(i, 1, n+1) {
			int x = pw(30);	
			rep(j, i+1, n+1) if (a[i] <= a[j] && a[j] < x) x = a[j], G.link(i + n, j, inf, 0);
		}	
		rep(i, 1, n+1) G.link(i, i + n, 1, -a[i]), G.link(i, i+n, inf, 0), G.link(s, i, inf, 0), G.link(i + n, t, inf, 0);
		pii ans = G.run(s, t);
		cout << -ans.se << endl;
	}
	return 0; 
}
