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

const int N = 150000 + 5;
const ll inf = 4e18;

int n, m, A;
int a[N];
ll ans;
vector<pii> g[N];
vi G[N];

bool vis[N];
int sz[N], par[N];
vector<pair<int, ll> > sum[N], sch[N];
struct LCARMQ {
	static const int N = ::N << 1;
	int a[20][N] , lft[N] , dep[N] , lg[N] , L, Dis[N];
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa){
		lft[c]=L;add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i].fi;
			if(t!=fa) dep[t]=dep[c]+1,Dis[t] = Dis[c] + g[c][i].se, dfs(t,c),add(c);
		}
	}
	void Build() {
		L = 0;dfs(1,0);dep[0] = -1;
		rep(i,2,L) lg[i]=lg[i>>1]+1;
		rep(i,1,20){
			int lim = L+1-(1<<i);
			rep(j,0,lim) a[i][j] = rmin(a[i-1][j] , a[i-1][j+(1<<i>>1)]);
		}
	}
	int lca(int x,int y){
		x = lft[x] , y = lft[y];
		if(x > y) swap(x , y);
		int i = lg[y-x+1];
		return rmin(a[i][x] , a[i][y+1-(1<<i)]);
	}
	int dis(int x, int y) {
		return Dis[x] + Dis[y] - 2 * Dis[lca(x, y)];
	}
}R;

void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	rep(i, 0, sz(g[c])) {
		int t = g[c][i].fi;
		if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
		if(!rt && sz[c] * 2 > Sz) rt = c;
	}
}
void dfs(int u, int v, int tp) {
	sch[tp].pb(mp(a[u], R.dis(u, v)));
	rep(i, 0, sz(G[u])) dfs(G[u][i], v, tp);
}
int dfs(int c) {
	int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
	rep(i, 0, sz(g[rt])) {
		int t = g[rt][i].fi;
		if(!vis[t]) {
			int v = dfs(t);
			par[v] = rt;
			G[rt].pb(v);
		}
	}
	sum[rt].pb(mp(a[rt], 0));
	rep(i, 0, sz(G[rt])) {
		int x = G[rt][i];
		dfs(x, rt, x);
		sort(all(sch[x]));
		sum[rt].insert(sum[rt].end(), all(sch[x]));
		rep(j, 1, sz(sch[x])) sch[x][j].se += sch[x][j - 1].se;
	}
	sort(all(sum[rt]));
	rep(i, 1, sz(sum[rt])) sum[rt][i].se += sum[rt][i - 1].se;
	return rt;
}

ll gao(int u, int v, int p, int L, int R) {
	if(u == v) {
		int r = upper_bound(all(sum[u]), mp(R, inf)) - sum[u].begin() - 1;
		int l = lower_bound(all(sum[u]), mp(L, 0ll))   - sum[u].begin();
		ll ans = (r >= 0 ? sum[u][r].se : 0) - (l ? sum[u][l - 1].se : 0);
		return ans;
	} else {
		int r = upper_bound(all(sum[u]), mp(R, inf)) - sum[u].begin() - 1;
		int l = lower_bound(all(sum[u]), mp(L, 0ll))   - sum[u].begin();
		int cr = upper_bound(all(sch[v]), mp(R, inf)) - sch[v].begin() - 1;
		int cl = lower_bound(all(sch[v]), mp(L, 0ll))   - sch[v].begin();
		int cnt = r - l + 1 - (cr - cl + 1);
		ll ans = cnt * 1ll * ::R.dis(u, p);
		ans += (r >= 0 ? sum[u][r].se : 0) - (l ? sum[u][l - 1].se : 0);
		ans -= (cr >= 0 ? sch[v][cr].se : 0) - (cl ? sch[v][cl - 1].se : 0);
		return ans;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> A;
	rep(i, 1, n + 1) cin >> a[i];
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	R.Build();
	int rt = dfs(1);
	while(m--) {
		int u, a, b;
		cin >> u >> a >> b;
		int L = (a + ans) % A, R = (b + ans) % A;
		if(L > R) swap(L, R);
		int v = u, p = u; ans = 0;
		while(1) {
			ll res = gao(u, v, p, L, R);
			ans += res;
			if(u == rt) break;
			v = u; u = par[u];
		}
		cout << ans << endl;
	}
	return 0;
}
