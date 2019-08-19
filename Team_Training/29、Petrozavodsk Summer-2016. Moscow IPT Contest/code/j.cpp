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
vi g[N];

int find(int x) {
	return x == pre[x] ? x : pre[x] = find(pre[x]);
}
void join(int x, int y) {
	x = find(x), y = find(y);
	pre[x] = y;
}

int L, hd[N], ne[N], val[N], las[N], sz[N];

void pb(int u, int v) {
	val[L] = v, ne[L] = hd[u];
	if(hd[u] == -1) las[u] = L;
	hd[u] = L++; sz[u]++;
}
void ins(int x, int y) {
	sz[x] += sz[y];
	ne[las[x]] = hd[y];
	las[x] = las[y];
	hd[y] = -1;
}
int fi(int u) {
	return val[hd[u]];
}
void gao(int x) {
	int u = 0, v = 0;
	for(int i = hd[x]; ~i; i = ne[i]) {
		v = val[i];
		if(u) join(u, v);
		u = v;
	}
	ne[hd[x]] = -1;
	las[x] = hd[x];
	sz[x] = 1;
}

struct LongChain{
	static const int N = ::N;
	int wson[N] , top[N] , dep[N];
	int id[N] , who[N] , _;
	void dfs(int c,int fa,vi g[]){
		dep[c]=1;int &s=wson[c]=top[c]=0;
		for(auto t:g[c]) if(t!=fa)
			dfs(t,c,g),dep[c]=max(dep[t]+1,dep[c]),(dep[t]>=dep[s])&&(s=t);
	}
	void dfs2(int c,int fa,vi g[]){
		if(!top[c]) top[c]=c;
		who[id[c]=++_]=c;
		int s=wson[c];
		if(s) top[s]=top[c],dfs2(s,c,g);
		for(auto t:g[c]) if(t!=fa&&t!=s) dfs2(t,c,g);
	}
	void Build(vi g[]){
		dfs(1,0,g);_=0;dfs2(1,0,g);
	}
	void solve(int c, int fa, vi g[]) {
		for(auto t : g[c]) if(t != fa) solve(t, c, g);
		pb(id[c], c);
		int md = min(d, dep[c] - 1);
		if(d == md) {
			gao(id[c]);
			gao(id[c] + d);
			join(fi(id[c]), fi(id[c] + d));
		}
		if(wson[c]) {
			int s = wson[c];
			for(auto t : g[c]) if(t != fa && t != s) {
				int td = min(d, dep[t]);
				rep(i, 1, td + 1) if(d - i <= md && sz[id[c] + d - i]) {
					gao(id[c] + d - i);
					gao(id[t] + i - 1);
					join(fi(id[c] + d - i), fi(id[t] + i - 1));
				}
				rep(i, 1, td + 1) ins(id[c] + i, id[t] + i - 1);
			}
		} 
	}
}hc;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> d;
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	if(d > n || d == 0) {
		cout << n << endl;
	} else if(d == 1) {
		cout << 1 << endl;
	} else {
		rep(i, 1, n + 1) pre[i] = i, hd[i] = las[i] = -1;
		hc.Build(g);
		hc.solve(1, 0, g);
		int ans = 0;
		rep(i, 1, n + 1) if(i == find(i)) ++ans;
		cout << ans << endl;
	}
	return 0;
}
