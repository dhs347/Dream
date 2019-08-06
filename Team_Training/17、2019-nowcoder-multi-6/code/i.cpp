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
const int P = 998244353;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 7;
int n, T, sum, ans[N], m, u, v, a, b;
vector<pii> g[N];
namespace BCC{
    const int N = 202020;
    vi key , dcc[N];
    int dfn[N] , low[N] , st[N] , _st , _, vis[N], id[N], use[N], fa[N];
    unordered_map<ll, int> M;
    ll ID(int u, int v) {
		if (u > v) swap(u, v);
		return 1ll * u * (n + 1) + v;
	}
    
    void dfs(int c,int dep,const vector<pii> g[]){
        int cc=0,out=1<dep;st[_st++]=c;
        dfn[c]=low[c]=dep;
        for(auto v:g[c]) {
            int t = v.fi;
			if(!dfn[t]){
                dfs(t,dep+1,g);
                low[c]=min(low[c],low[t]);
                if(low[t]>=dfn[c]){
                    //if(++out==2) key.pb(c);
                    int now = c;
					while(st[--_st]!=t) {
						M[ID(st[_st], now)] = _;
						//dcc[st[_st]].pb(_);
						now = st[_st];
                	}
					//dcc[c].pb(_);dcc[t].pb(_++);
					M[ID(t, now)] = _;
					M[ID(c, t)] = _;
					_++;
                }
            } else if(dfn[t] != dfn[c] - 1 || cc++)
                low[c] = min(low[c] , dfn[t]);
		}
    }
    
    void get1(int u, vector<pii> g[], vi &tmp, int w, int pre, int id) {
		vis[u] = 1; tmp.pb(u); ans[u] = add(1, -w); fa[u] = pre;
		for (auto v : g[u]) {
			ll t = ID(u, v.fi);
			if (!use[v.fi] && !vis[v.fi] && (id == -1 || (M.count(t) && M[t] == id))) 
				get1(v.fi, g, tmp, mul(w, v.se), u, id == -1 ? M[t] : id);
		}
	}
    
    void get2(int u, vector<pii> g[], int w, int pre, int id) { 
		vis[u] = 0; 
		if (pre != fa[u]) ans[u] = add(1, -mul(ans[u], add(1, -w)));
		else ans[u] = add(1, -ans[u]);
		per(i, 0, sz(g[u])) {
		 	auto v = g[u][i]; 
		 	ll t = ID(u, v.fi);
			if (!use[v.fi] && vis[v.fi] && (id == -1 || (M.count(t) && M[t] == id))) {
				get2(v.fi, g, mul(w, v.se), u, id == -1 ? M[t] : id);
			}
		}
	}
    
    void dfs2(int u, vector<pii> g[], int w) {
		vi tmp; 
		get1(u, g, tmp, 1, 0, -1);
		get2(u, g, 1, 0, -1);
		for (auto v : tmp) use[v] = 1;
		for (auto v : tmp) {
			ans[v] = mul(ans[v], w);
			if (v != u) dfs2(v, g, ans[v]);
		}
	}
    
    int solve(int n,vector<pii> g[]){
    	M.clear();
        fill_n(dfn,n+1,_=0);
        fill_n(low,n+1,_st=0);
        //fill_n(dcc,n+1,key=vi());
        fill_n(use,n+1,0);
        rep(i,1,n+1) if(!dfn[i]) dfs(i,1,g);
        //rep(i,1,n+1) if(sz(dcc[i]) == 0) dcc[i].pb(_++);
		dfs2(1, g, 1);
        return _;
    }
};

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> T;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, n+1) g[i].clear();
		rep(i, 1, m+1) {
			cin >> u >> v >> a >> b;
			a = mul(a, kpow(b, P - 2));
			g[u].pb(mp(v, a));
			g[v].pb(mp(u, a)); 
		}
		rep(i, 1, n+1) ans[i] = 0;
		BCC :: solve(n, g);
		sum = 0;
		rep(i, 1, n+1) sum = add(sum, ans[i]);
		cout << "Case #" << cas+1 << ": " << sum << endl;
	}
	return 0; 
}


