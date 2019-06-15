#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 202020;
const ll inf = 1e18;

int n, m, k, to[N];
ll dis[N], ans[N];
vector<pii> g2[N], g[N], in[N], out[N], tot[N];

struct LCARMQ{
	static const int N = ::N << 1;
	int a[20][N] , lft[N] , dep[N] , lg[N] , L;
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa,const vector<pii> g[]){
		lft[c]=L;add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i].fi;
			if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
		}
	}
	void Build(const vector<pii> g[]){
		L = 0;dfs(1,0,g);dep[0] = -1;
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
	int lcadep(int x, int y) {
		return dep[lca(x, y)];
	}
}R;

bool cmp(pii a, pii b) {
	return a.se < b.se;
}
bool cmp2(pii a, pii b) {
	return R.lft[a.fi] < R.lft[b.fi];
}

void solve() {
	cin >> n >> m >> k;
	rep(i, 1, n + 1) in[i].clear(), out[i].clear(), tot[i].clear(), ans[i] = inf;
	rep(i, 1, k + 1) g2[i].clear();
	rep(i, 0, m << 2) g[i].clear(), dis[i] = inf;
	priority_queue<pair<ll, int> > que;
	rep(i, 0, m) {
		int u, v, w, d;
		cin >> u >> v >> w >> d;
		in[v].pb(mp(d, i));
		out[u].pb(mp(d, i));
		tot[u].pb(mp(d, i));
		tot[v].pb(mp(d, i));
		to[i] = v;
		if(u == 1) dis[i << 2] = dis[i << 2 | 1] = 0, que.push(mp(0, i << 2)), que.push(mp(0, i << 2 | 1));
		rep(a, 0, 2) rep(b, 2, 4) g[i << 2 | a].pb(mp(i << 2 | b, w));
	}
	rep(i, 1, k) {
		int u, v, w;
		cin >> u >> v >> w;
		g2[u].pb(mp(v, w));
	}
	rep(i, 1, k + 1) sort(all(g2[i]), cmp);
	R.Build(g2);
	rep(i, 1, n + 1) {
		sort(all(in[i]), cmp2);
		sort(all(out[i]), cmp2);
		sort(all(tot[i]), cmp2);
		rep(j, 0, sz(in[i]) - 1) g[in[i][j].se << 2 | 3].pb(mp(in[i][j + 1].se << 2 | 3, 0));
		rep(j, 0, sz(out[i]) - 1) g[out[i][j].se << 2 | 1].pb(mp(out[i][j + 1].se << 2 | 1, 0));
		rep(j, 1, sz(in[i])) g[in[i][j].se << 2 | 2].pb(mp(in[i][j - 1].se << 2 | 2, 0));
		rep(j, 1, sz(out[i])) g[out[i][j].se << 2].pb(mp(out[i][j - 1].se << 2, 0));
		rep(j, 1, sz(tot[i])) {
			int dl = tot[i][j - 1].fi, dr = tot[i][j].fi, h = R.lcadep(dl, dr);
			int ir = upper_bound(all(in[i]), tot[i][j - 1], cmp2) - in[i].begin(), il = ir - 1;
			int ro = lower_bound(all(out[i]), tot[i][j], cmp2) - out[i].begin(), ol = ro - 1;
			if(il >= 0 && ro < sz(out[i])) {
				int u = in[i][il].se, v = out[i][ro].se;
				g[u << 2 | 3].pb(mp(v << 2 | 1, h));
			}
			if(ir < sz(in[i]) && ol >= 0) {
				int u = in[i][ir].se, v = out[i][ol].se;
				g[u << 2 | 2].pb(mp(v << 2, h));
			}
		}
	}
	while(!que.empty()) {
		pair<ll, int> u = que.top(); que.pop();
		if(-u.fi == dis[u.se]) {
			rep(i, 0, sz(g[u.se])) {
				pii v = g[u.se][i];
				if(dis[v.fi] > dis[u.se] + v.se) {
					dis[v.fi] = dis[u.se] + v.se;
					que.push(mp(-dis[v.fi], v.fi));
				}
			}
		}
	}
	rep(i, 0, m) ans[to[i]] = min(ans[to[i]], min(dis[i << 2 | 2], dis[i << 2 | 3]));
	rep(i, 2, n + 1) cout << ans[i] << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T;
	cin >> T;
	while(T--) solve();
	return 0;
}
