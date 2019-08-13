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

const int N = 101010, P = 1e9 + 7;

int n, m, s, k, inv[N], f[N], h[N], deg[N], tmp[N];
char str[N];
vi G[N], g[N << 1];

void adde(int u, int v) { g[u].pb(v), g[v].pb(u); /*dd(u), de(v); */}

// cactus: n multi by 2
// key is cuts
// dcc i->j , i(points) , j(bcc_block)
// st is stack
// _st is top of stack
// _ is number of dcc
// can handle isolate point and not connected graph and muti edge 
// can handle self circle ? 
namespace DCC{
	const int N = 202020;
	vi key , dcc[N];
	int dfn[N] , low[N] , st[N] , _st , _;
	void dfs(int c,int dep,const vi g[]){
		int cc=0,out=1<dep;st[_st++]=c;
		dfn[c]=low[c]=dep;
		for(auto t:g[c])
			if(!dfn[t]){
				dfs(t,dep+1,g);
				low[c]=min(low[c],low[t]);
				if(low[t]>=dfn[c]){
					if(++out==2) key.pb(c);
					++k;
					while(st[--_st]!=t) {
						dcc[st[_st]].pb(_);
						adde(k, st[_st] + 1);
					}
					dcc[c].pb(_);dcc[t].pb(_++);
					adde(k, t + 1); adde(k, c + 1);
				}
			} else if(dfn[t] != dfn[c] - 1 || cc++)
				low[c] = min(low[c] , dfn[t]);
	}
	int solve(int n,const vi g[]){// n is size of points
		fill_n(dfn,n,_=0);
		fill_n(low,n,_st=0);
		fill_n(dcc,n,key=vi());
		rep(i,0,n) if(!dfn[i]) dfs(i,1,g);
		rep(i,0,n) if(sz(dcc[i]) == 0) dcc[i].pb(_++);
		//de(_);
		return _;
	}
}
int add(int a, int b) {
	if((a += b) >= P) a -= P;
	return a;
}
int mul(int a, int b) {
	return 1ll * a * b % P;
}
// assert(u <= n)
void dfs(int u, int fa) {
	for(auto t : g[u]) if(t != fa) {
		// assert(t > n);
		auto _ = g[t]; bool ok = 0; g[t].clear();
		for(auto v : _) {
			if(ok) g[t].pb(v);
			if(v == u) ok = 1;
		}
		for(auto v : _) {
			if(v == u) break;
			g[t].pb(v);
		}
		//de(t);
		if(sz(g[t]) >= 2) {
			int pre = u, las; tmp[u] = f[u];
			for(auto v : g[t]) {
				tmp[v] = mul(tmp[pre], inv[deg[pre]]);
			//	dd(v), de(tmp[v]);
				pre = las = v;
			} if(sz(g[las]) == 1) h[las] = tmp[las];
		//	dd(las), dd(tmp[las]);
			tmp[las] = mul(tmp[las], mul(deg[las], inv[deg[las] - 1]));
		//	de(tmp[las]);

			pre = u;
			per(i, 0, sz(g[t])) {
				int v = g[t][i];
				f[v] = mul(f[pre], inv[deg[pre]]);
				//dd(v), de(f[v]);
				pre = las = v;
			} if(sz(g[las]) == 1) h[las] = f[las];
		//	dd(las);dd(f[las]);
			f[las] = mul(f[las], mul(deg[las], inv[deg[las] - 1]));
		//	de(f[las]);

			for(auto v : g[t]) f[v] = add(f[v], tmp[v]);
		} else {
			for(auto v : g[t]) if(v != u) {
				f[v] = mul(f[u], inv[deg[u]]);
				if(sz(g[v]) == 1) h[v] = f[v];
			}
		}
		for(auto v : g[t]) dfs(v, t); //dd(u), dd(t), de(v), dfs(v, t);
	}
}
int kpow(int a, int b) {
	int r = 1;
	while(b) {
		if(b & 1) r = r * 1ll * a % P;
		a = a * 1ll * a % P;
		b >>= 1;
	}
	return r;
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m >> s >> (str + 1);
	inv[1] = 1; rep(i, 2, n + 1) inv[i] = inv[P % i] * 1ll * (P - P / i) % P, assert(mul(i, inv[i]) == 1);
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		--u, --v;
		G[u].pb(v), G[v].pb(u);
	}
	rep(i, 1, n + 1) deg[i] = sz(G[i - 1]) - (i != s);
	k = n; DCC::solve(n, G);
	f[s] = 1; dfs(s, 0);
	int G = 0, R = 0;
	rep(i, 1, n + 1) {
		if(str[i] == 'G') G = add(G, h[i]);
		if(str[i] == 'R') R = add(R, h[i]);
	}
	//rep(i, 1, n + 1) dd(i), dd(f[i]), dd(h[i]), de(f[i] * 4ll % P * inv[3] % P);
	int fz = R, fm = add(R, G);
	if(fm == 0) {
		cout << "NaN" << endl;
	} else {
		cout << mul(fz, kpow(fm, P - 2)) << endl;
	}
	return 0;
}
