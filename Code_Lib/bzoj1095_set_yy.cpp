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

const int N = 101010;

int n, rt;
int par[N], col[N], r1[N], r2[N];
vi g[N], G[N];
priority_queue<pii> q1[N], q2[N], ans;

// N is 2 size of tree , id of nodes start from 1
struct LCARMQ{
	static const int N = 101010 << 1;
	int a[20][N] , lft[N] , dep[N] , lg[N] , L;
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
		return dep[x] + dep[y] - 2 * dep[lca(x, y)];
	}
}R;

// id starts from 1
namespace Centriod {
	const int N = ::N;
	bool vis[N];
	int sz[N];
	void dfssz(int c,int fa,int Sz,int &rt){
		sz[c] = 1;
		rep(i, 0, sz(g[c])) {
			int t = g[c][i];
			if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
		}
		if(!rt && sz[c]*2>Sz) rt=c;
	}
	void dfs(int u, int rt, int tp) {
		q1[tp].push(mp(R.dis(u, rt), u));
		rep(i, 0, sz(G[u])) dfs(G[u][i], rt, tp);
	}
	int dfs(int c){
		int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
		vis[rt] = true;
		rep(i, 0, sz(g[rt])) {
			int v = g[rt][i];
			if(!vis[v]) {
				int t = dfs(v);
				G[rt].pb(t);
				par[t] = rt;
			}
		}
		rep(i, 0, sz(G[rt])) {
			int v = G[rt][i];
			dfs(v, rt, v);
			if(!q1[v].empty()) q2[rt].push(mp(q1[v].top().fi, v)), r1[v] = q1[v].top().fi;
			else r1[v] = -1;
		}
		q2[rt].push(mp(0, rt));
		vector<pii> res;
		while(!q2[rt].empty() && sz(res) < 2) {
			res.pb(q2[rt].top());
			q2[rt].pop();
		}
		int &r = r2[rt] = 0;
		rep(i, 0, sz(res)) q2[rt].push(res[i]), r += res[i].fi;
		ans.push(mp(r, rt));
		return rt;
	}
};

void gao(int p, int v, int u) {
	if(p == u) {
		if(!col[u]) q2[u].push(mp(0, u));
	} else {
		if(!col[p]) q1[v].push(mp(R.dis(p, u), p));
		r1[v] = -1;
		while(!q1[v].empty()) {
			pii t = q1[v].top();
			if(!col[t.se]) {
				r1[v] = t.fi;
				q2[u].push(mp(t.fi, v));
				break;
			}
			q1[v].pop();
		}
	}
	vector<pii> res;
	while(!q2[u].empty() && sz(res) < 2) {
		pii t = q2[u].top();
		if(t.se == u ? !col[t.se] : t.fi == r1[t.se]) res.pb(t);
		q2[u].pop();
	}
	int &r = r2[u] = 0;
	rep(i, 0, sz(res)) q2[u].push(res[i]), r += res[i].fi;
	if(sz(res) == 0 || (sz(res) == 1 && col[u])) r = -1;
	ans.push(mp(r, u));
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
	rt = Centriod::dfs(1);
	int m;
	cin >> m;
	rep(_, 1, m + 1) {
		string o;
		cin >> o;
		if(o[0] == 'G') {
			int res = -1;
			while(!ans.empty()) {
				pii t = ans.top();
				int val = r2[t.se];
				if(t.fi != val) {
					ans.pop();
				} else {
					res = val;
					break;
				}
			}
			cout << res << endl;
		} else {
			int u;
			cin >> u;
			col[u] ^= 1;
			int v = u, pre = u;
			while(1) {
				gao(u, pre, v);
				pre = v;
				if(v == rt) break;
				v = par[v];
			}
		}
	}
	return 0;
}
