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

int n;
int par[N], col[N], Res[N], Ans[N];
vi g[N], G[N];

struct Heap {
	priority_queue<int> que, del;
	void Push(int x) {
		que.push(x);
	}
	void Del(int x) {
		del.push(x);
	}
	int Top() {
		while(!que.empty()) {
			if(!del.empty() && que.top() == del.top()) que.pop(), del.pop();
			else return que.top();
		}
		return -1;
	}
	int Top2() {
		vi res;
		while(!que.empty() && sz(res) < 2) {
			if(!del.empty() && que.top() == del.top()) que.pop(), del.pop();
			else res.pb(que.top()), que.pop();
		}
		rep(i, 0, sz(res)) que.push(res[i]);
		return (sz(res) == 2 ? res[1] : -1);
	}
}ch[N], que[N], ans;

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
		ch[tp].Push(R.dis(u, rt));
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
			int &tp = Ans[v] = ch[v].Top();
			if(~tp) que[rt].Push(tp);
		}
		que[rt].Push(0);
		vi res;
		res.pb(que[rt].Top());
		res.pb(que[rt].Top2());
		int r = 0;
		rep(i, 0, sz(res)) if(~res[i]) r += res[i];
		Res[rt] = r;
		ans.Push(r);
		return rt;
	}
};

void gao(int p, int v, int u) {
	if(v == u) {
		if(col[p]) {
			que[u].Del(0);
		} else {
			que[u].Push(0);
		}
	} else {
		int &tp = Ans[v];
		if(~tp) que[u].Del(tp);
		if(col[p]) {
			ch[v].Del(R.dis(p, u));
		} else {
			ch[v].Push(R.dis(p, u));
		}
		tp = ch[v].Top();
		if(~tp) que[u].Push(tp);
	}
	ans.Del(Res[u]);
	int t = que[u].Top(), t2 = que[u].Top2();
	vi res;
	if(~t) res.pb(t);
	if(~t2) res.pb(t2);
	int &r = Res[u] = 0;
	rep(i, 0, sz(res)) r += res[i];
	if(sz(res) == 0 || (sz(res) == 1 && col[u])) r = -1;
	ans.Push(r);
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
	int rt = Centriod::dfs(1);
	int m; cin >> m;
	while(m--) {
		string o;
		cin >> o;
		if(o[0] == 'G') {
			cout << ans.Top() << endl;
		} else {
			int p; cin >> p;
			col[p] ^= 1;
			int u = p, v = p;
			while(1) {
				gao(p, v, u);
				if(u == rt) break;
				v = u;
				u = par[u];
			}
		}
	}
	return 0;
}
