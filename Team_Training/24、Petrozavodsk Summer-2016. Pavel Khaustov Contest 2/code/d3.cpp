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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef vector<pii> vii;

const int N = 1 << 9;
vector<pair<int, vii> > fang[N];
int f[100][N][30], n, m, S, a[100][100], b[100][100], ss[100];
string s[100];
void dfs(int n, int s1, int s2, vii tmp, int pp) {
	if (s1 == S) {
		fang[pp].pb(mp(s2, tmp));
		return;
	}
	rep(i, 0, n) if (!(pw(i) & s1)) {
		tmp.pb(mp(i, 0));
		dfs(n, s1 + pw(i), s2 + pw(i), tmp, pp);
		tmp.pop_back();
		if (i + 1 < n && !(pw(i + 1) & s1)) {
			tmp.pb(mp(i, 1));
			dfs(n, s1 + pw(i) + pw(i + 1), s2, tmp, pp);
		}
		break;
	}
}

pii aa[N];

const int inf = 1e9 + 7;
template<class U, class V> 
struct MCMF{
	static const int N = 2005, M = 101010;
	int h[N], ing[N], pre[N], to[M], ne[M], e, s, t, n;
	U cap[M]; V dis[N], cost[M];
	void ini(int _n = N) { fill(h, h+(n= _n), -1); e =0;}
	void liu(int u, int v, U c, V w) {
		to[e] = v; ne[e] = h[u]; cap[e] = c; cost[e] = w; 
		h[u] = e++;
	}
	void link(int u, int v, U c, V w) {
		liu(u, v, c, w);
		liu(v, u, 0, -w);
	}
	bool spfa() {
		queue<int> q;
		fill(dis, dis+n, inf);
		ing[s] = 1; dis[s] = 0;
		q.push(s);
		while (!q.empty()) {
			int c = q.front(); q.pop(); ing[c] = 0;
			for (int k = h[c]; ~k; k = ne[k]) {
				int v = to[k];
				if (cap[k] <= 0) continue;
				if (dis[c] + cost[k] < dis[v]) {
					dis[v] = dis[c] + cost[k];
					pre[v] = k;
					if (!ing[v]) q.push(v), ing[v] = 1;

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
			for (p= t; p != s; p = to[k ^ 1]) pl = min(pl, cap[k = pre[p]]);
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

MCMF<int, int> G;
int ans[30][30];
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int cas = 0, cnt = 0;
	per(i, 0, 7) rep(j, 0, i+1) {
		aa[++cnt] = mp(i, j);
	}
	rep(i, 0, 29) rep(j, 0, 29) {
		if (i + j > 28) break;
		G.ini(200); 
		int s = G.n - 5, t = s + 1, tt = t + 1, ttt = t + 2;
		rep(k, 1, cnt+1) {
			G.link(s, k, 1, 0);
			G.link(k, tt, 1, -(aa[k].fi + aa[k].se));
			G.link(k, ttt, 1, -(aa[k].fi));
		} 
		G.link(tt, t, i, 0);
		G.link(ttt, t, j, 0);
		ans[i][j] = -G.run(s, t).se;
		//de(ans[i][j]);
	}
	
	while (cin >> n >> m) {
		cas++;
		if (n == 0 && m == 0) break;
		rep(i, 0, n) cin >> s[i];
		rep(i, 0, n) rep(j, 0, m) {
			if (s[i][j] == 'B') a[i][j] = 1;
			else if (s[i][j] == 'W') a[i][j] = 0;
			else a[i][j] = 2;
		}
		if (n < m) {
			rep(i, 0, n) rep(j, 0, m) b[j][i] = a[i][j];
			swap(n, m);
			rep(i, 0, n) rep(j, 0, m) a[i][j] = b[i][j];	
		}

		rep(i, 0, n+1) ss[i] = 0;
		rep(i, 0, n) {
				rep(j, 0, m) if (a[i][j] == 1) ss[i] |= pw(j);
			}
	//	rep(i, 0, n+1) ss[i] = 0;
		S = pw(m) - 1;
		rep(i, 0, S+1) fang[i].clear(), dfs(m, i, 0, vii(), i);
		rep(i, 0, n+1) rep(j, 0, S+1) rep(k, 0, 30) f[i][j][k] = -1;
		f[0][ss[0]][0] = 0;
		rep(i, 0, n) rep(j, 0, S+1) {
			rep(k, 0, 29) if (f[i][j][k] != -1) {
				for (auto u : fang[j]) {
					int &p = u.fi;
					vii &t = u.se;
					if ((p & ss[i+1]) == 0) {
						int c1 = 0, c2 = 0;
						for (auto x : t) {
							int y = 0;
							if (!x.se) {
								y += a[i][x.fi] == 2;
								y += a[i+1][x.fi] == 2;
							}else {	
								y += a[i][x.fi] == 2;
								y += a[i][x.fi+1] == 2;
							}
							if (y == 2) c2++;
							else if (y == 1) c1++;
						}
						f[i+1][p | ss[i+1]][k+c2] = max(f[i+1][p | ss[i+1]][k+c2], f[i][j][k] + c1);
					}
				} 
			} 
		}
		int an = 0, ok = 0;
		rep(i, 0, 29) {
			int t = f[n][0][i];
			if (t != -1) ok  = 1, an = max(an, ans[i][t]);
		}
		cout << "Case " << cas << ": ";
		if (ok) cout << an; else cout << "No solution";
		cout << endl;
	}
	return 0;
}
