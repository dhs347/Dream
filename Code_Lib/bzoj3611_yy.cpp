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

const int N = 1e6 + 7;

int n;
vi g[N];

// N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
	static const int N = ::N << 1, M = 23;
	int a[M][N] , lft[N] , dep[N] , lg[N] , L;
	int rmin(int x,int y){return dep[x] < dep[y] ? x : y;}
	void add(int x){ a[0][L++] = x;}
	void dfs(int c,int fa,const vi g[]){
		lft[c]=L;add(c);
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(t!=fa) dep[t]=dep[c]+1,dfs(t,c,g),add(c);
		}
	}
	void Build(const vi g[]){
		L = 0;dfs(1,0,g);dep[0] = -1;
		rep(i,2,L) lg[i]=lg[i>>1]+1;
		rep(i,1,M){
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
		return abs(dep[x] - dep[y]);
	}
}R;

bool cmp(int a, int b) {
	return R.lft[a] < R.lft[b];
}

// nodes should sorted in dfs order
namespace Vtree{
	const int N = ::N;
	int tp[N] , _;
	vi g[N];
	int tim, vis[N], tot, sz[N], ma[N], mi[N], ma2[N], mi2[N];
	ll r1; int r2, r3;
	void dfs(int u) {
		sz[u] = (vis[u] == tim);
		ma[u] = 0; mi[u] = (vis[u] == tim ? 0 : N);
		rep(i, 0, sz(g[u])) {
			int v = g[u][i];
			dfs(v);
			r1 += sz[v] * 1ll * (tot - sz[v]) * R.dis(u, v);
			sz[u] += sz[v];
			ma[u] = max(ma[u], ma[v] + R.dis(u, v));
			mi[u] = min(mi[u], mi[v] + R.dis(u, v));
		}
	}
	void dfs2(int u) {
		int pma = 0, pmi = (vis[u] == tim ? 0 : N);
		rep(i, 0, sz(g[u])) {
			int v = g[u][i];
			ma2[v] = max(ma2[u], pma) + R.dis(u, v);
			mi2[v] = min(mi2[u], pmi) + R.dis(u, v);
			pma = max(pma, ma[v] + R.dis(u, v));
			pmi = min(pmi, mi[v] + R.dis(u, v));
		}
		pma = 0, pmi = N;
		per(i, 0, sz(g[u])) {
			int v = g[u][i];
			ma2[v] = max(ma2[v], pma + R.dis(u, v));
			mi2[v] = min(mi2[v], pmi + R.dis(u, v));
			pma = max(pma, ma[v] + R.dis(u, v));
			pmi = min(pmi, mi[v] + R.dis(u, v));
			if(sz[v] < tot) {
				r2 = min(r2, mi2[v] + mi[v]);
				r3 = max(r3, ma2[v] + ma[v]);
			}
			dfs2(v);
		}
	}
	void solve(vi&v,LCARMQ&R){
		++tim; rep(i, 0, sz(v)) vis[v[i]] = tim;
		r1 = r3 = 0; r2 = N; tot = sz(v);
		_ = 0;
		vi del;del.pb(tp[_++] = v[0]);
		rep(i,1,sz(v)){
			int lca = R.lca(tp[_-1] , v[i]);
			vi l;while(_ > 0 && R.dep[lca] < R.dep[tp[_-1]]) l.pb(tp[--_]);
			if(_ == 0 || lca != tp[_-1]) del.pb(tp[_++] = lca);
			l.pb(tp[_-1]);del.pb(tp[_++] = v[i]);
			rep(i,1,sz(l)) g[l[i]].pb(l[i-1]);
		}
		rep(i,0,_-1) g[tp[i]].pb(tp[i+1]);
		dfs(tp[0]);
		ma2[tp[0]] = 0; mi2[tp[0]] = (vis[tp[0]] == tim ? 0 : N);
		dfs2(tp[0]);
		cout << r1 << " " << r2 << " " << r3 << endl;
		rep(i, 0, sz(del)) g[del[i]].clear();
	}
}


int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v;
		cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	R.Build(g);
	int m;
	cin >> m;
	while(m--) {
		int k; cin >> k;
		vi v;
		rep(i, 0, k) {
			int x; 
			cin >> x;
			v.pb(x);
		}
		sort(all(v), cmp);
		Vtree::solve(v, R);
	}
	return 0;
}
