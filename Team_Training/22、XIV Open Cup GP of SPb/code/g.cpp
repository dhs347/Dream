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
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef __int128 ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;


const int N = 3005;
ll inf;
int an[N], B, x, y, n, k, s, t;
ll b[50];

template<class U, class V> 
struct MCMF{
	static const int N = 3040, M = 101010;
	int h[N], ing[N], pre[N], to[M], ne[M], e, s, t, n;
	U cap[M]; V dis[N], cost[M];
	void ini(int _n = N) {fill(h, h+ (n = _n), -1); e = 0;}
	void liu(int u, int v, U c, V w) {
		to[e] = v; ne[e] = h[u]; cap[e] = c; cost[e] = w; h[u] = e++;
	}
	void link(int u, int v, U c, V w) {
		liu(u, v, c, w);
		liu(v, u, 0, -w);
	}
	bool spfa() {
		queue<int> Q;
		fill(dis, dis+n, inf);
		ing[s] = 1, dis[s] = 0;
		Q.push(s);
		while (!Q.empty()) {
			int c = Q.front(); Q.pop(); ing[c] = 0;
			for (int k = h[c]; ~k; k = ne[k]) {
				int v = to[k];
				if (cap[k] <= 0) continue;
				if (dis[c] + cost[k] < dis[v]) {
					dis[v] = dis[c] + cost[k];
					pre[v] = k; 
					if (!ing[v]) Q.push(v), ing[v] = 1;
				}
			}
		}
		return dis[t] <= 0;
	}
	U flow; V mincost;
	pair<U, V> run(int _s, int _t) {
		s = _s, t = _t;
		while (spfa()) {
			U pl = inf; int p, k;
			for (p = t; p != s; p = to[k^1]) pl = min(pl, cap[k = pre[p]]);
			for (p = t; p != s; p = to[k ^ 1]) {
				k = pre[p];
				cap[k] -= pl;
				cap[k ^ 1] += pl;
			}
			mincost += pl * dis[t];
			flow += pl;
		}
		return mp(flow, mincost);
	}
};

MCMF<int, ll> G;

int pos[N];

int main() {
	freopen("medals.in", "r", stdin);
	freopen("medals.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	G.ini(n + 1200);
	b[10] = 1; B = 1001;
	per(i, 1, 10) b[i] = b[i+1] * B;
	inf =  b[1] * (B + 10);
	s = G.n - 5; t = s + 1;
	rep(i, 1, n+1) {
		cin >> k;
		rep(j, 0, k) {
			cin >> x >> y;
			G.link(i, x + n, 1, -b[y]);
		}
		G.link(s, i, 1, 0);
	}
	rep(i, 1, 1001) G.link(n + i, t, 1, 0);
	auto ans = -G.run(s, t).se;
	int p = 10;
	while (ans) {
		an[p] = ans % B;
		ans /= B;
		p--;
	}
	for (int i = 0; i < G.e; i += 2) {
		int u = G.to[i ^ 1], v = G.to[i];
		if (u != s && v != t && G.cap[i] == 0) {
			pos[u] = v - n; 
		}
	}
	rep(i, 1, 11) cout << an[i] << " \n"[i == 10];
	rep(i, 1, n+1) cout << pos[i] << " \n"[i == n];
	return 0;
}
