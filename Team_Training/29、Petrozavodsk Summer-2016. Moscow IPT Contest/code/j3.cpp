#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 1e6 + 7;

int n, d, pre[N];
int h[N];
vi g[N];

int vec[N], cntv;
int dep[N], maxdep, md, mmd[N];
int ssz[N];

int sx[N * 3], sy[N * 3], nex[N * 3], ney[N * 3], m1, m2, tox[N * 3], toy[N * 3];

inline int find(register int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
inline void join(register int x, register int y) {
	x = find(x), y = find(y);
	if(x == y) return ;
	if(h[x] > h[y]) swap(x, y);
	h[y] += h[x];
	pre[x] = y;
}


inline void gao(register int l, int *ne, int *to){
	register int now = to[l];
	l = ne[l];
	while (l) {
		join(now, to[l]);
		l = ne[l];
	}
	ne[l] = 0;
}


namespace Cen {
	const int N = ::N;
	bool vis[N];
	int sz[N];
	void dfssz(int c, int fa, int Sz, int &rt) {
		sz[c] = 1;
		for(auto t : g[c]) if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
		if(!rt && sz[c] * 2 > Sz) rt = c;
	}
	void dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		vec[++cntv] = u;
		md = max(md, dep[u]);
		if(dep[u] < d) for(auto v : g[u]) if(v != fa && !vis[v]) dfs(v, u);
	}
	void dfs(int c) {
		int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
		vis[rt] = 1;

		maxdep = 0;
		m1++; nex[m1] = sx[0]; sx[0] = m1; tox[m1] = rt;
		dep[rt] = 0;
		for(auto u : g[rt]) if(!vis[u]) {
			cntv = md = 0; dfs(u, rt);
			rep(i, 0, md+1) sy[i] = 0;
			m2 = 0;
			
			rep(i, 1, cntv+1) {
				++m2, ney[m2] = sy[dep[vec[i]]], toy[m2] = vec[i]; sy[dep[vec[i]]] = m2;
			}
			
			rep(i, 1, md + 1) if(d - i <= maxdep) {
				gao(sx[d - i], nex, tox);
				gao(sy[i], ney, toy);
				join(tox[sx[d - i]], toy[sy[i]]);
			}
			rep(i, 0, md + 1) {
				for (int l = sy[i]; l; l = ney[l]) {
					m1++; nex[m1] = sx[i]; sx[i] = m1; tox[m1] = toy[l];
				}
			}
			maxdep = max(maxdep, md);
			mmd[u] = md - 1;
			ssz[u] = cntv;
		}

		rep(i, 0, maxdep + 1) sx[i] = 0;//sx[i].clear();
		m1 = 0;
		for(auto t : g[rt]) if(!vis[t] && 2 * mmd[t] >= d && ssz[t] >= d) dfs(t);
	}
};

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> d;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	if(d == 0) {
		cout << n << endl;
	} else if(d == 1) {
		cout << 1 << endl;
	} else {
		rep(i, 1, n + 1) pre[i] = i, h[i] = 1;;
		Cen::dfs(1);
		int ans = 0;
		rep(i, 1, n + 1) ans += i == find(i);
		cout << ans << endl;
	}
	return 0;
}
