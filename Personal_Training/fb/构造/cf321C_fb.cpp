#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) (a).begin(), (a).end()
#define pw(x) (1ll<<(x))
#define lb(x) ((x) & -(x))
#define endl "\n"
#define FI(x) freopen(#x".in","r",stdin)
#define FO(x) freopen(#x".out","w",stdout)
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
//typedef uniform_int_distribution<ll> RR;
//mt19937 gen(998244353);
//ll rnd(ll l, ll r) { RR dis(l, r); return dis(gen); }
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;

namespace Centriod {
	const int N = ::N;
	int n;
	bool vis[N]; int sz[N], par[N]; vi G[N], g[N];
	char ans[N];
	void dfssz(int c,int fa,int Sz,int &rt){
		sz[c] = 1;
		for(auto t : g[c]) if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
		if(!rt && sz[c]*2>Sz) rt=c;
	}
	int dfs(int c, char w){
		int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
		vis[rt] = true; ans[rt] = w;
		for(auto v : g[rt]) if(!vis[v]) {
			int t = dfs(v, w+1);
			G[rt].pb(t);
			par[t] = rt;
		}
		return rt;
	}
	void init() { 
		fill_n(G + 1, n, vi()); 
		fill_n(par + 1, n, 0);
	}
	void solve() {
		cin >> n;
		rep(i, 1, n) {
			int u, v;
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		dfs(1, 'A');
		rep(i, 1, n+1) cout << ans[i] << " \n"[i == n];
	}
};

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	Centriod :: solve(); 
	return 0;
}


