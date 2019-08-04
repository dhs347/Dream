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
    vi key , bcc[N];
    int dfn[N] , low[N] , id[N] , st[N] , _st , _;
    bool vis[N], use[N];
    void dfs(int c,int dep,vector<pii> g[]){
        int cc=0;st[_st++]=c;
        dfn[c]=low[c]=dep;
        for(auto e:g[c]){
            int t=e.fi;
            if(!dfn[t]){
                dfs(t,dep+1,g);
                low[c]=min(low[c],low[t]);
               // if(low[t]>dfn[c]) key.pb(e.se);
            } else if(dfn[t] != dfn[c] - 1 || cc++)
                low[c] = min(low[c] , dfn[t]);
        }
        if(low[c]==dfn[c]){
            do{id[st[--_st]]=_;}while(st[_st]!=c);
            _++;
        }
    }
    
    void get1(int u, vector<pii> g[], vi &tmp, int w) {
		vis[u] = 1; tmp.pb(u); ans[u] = add(1, -w);
		for (auto v : g[u]) if (id[v.fi] == id[u] && !vis[v.fi]) {
			get1(v.fi, g, tmp, mul(w, v.se));
		}
	}
    
    void get2(int u, vector<pii> g[], int w) { 
		vis[u] = 0; ans[u] = add(1, -mul(ans[u], add(1, -w)));
		per(i, 0, sz(g[u])) {
		 	auto v = g[u][i]; 
			if (id[v.fi] == id[u] && vis[v.fi]) {
				get2(v.fi, g, mul(w, v.se));
			}
		}
	}
    
    void dfs2(int u, vector<pii> g[], int w) {
    	use[id[u]] = 1;
		vi tmp; 
		get1(u, g, tmp, 1);
		get2(u, g, 1);
		for (auto v : tmp) {
			ans[v] = mul(ans[v], w);
			for (auto vv : g[v]) if (!use[id[vv.fi]]) dfs2(vv.fi, g, mul(ans[v], vv.se));
		}
	}
    
    int solve(int n,vector<pii> g[]){
        fill_n(dfn,n+1,_=0);
        fill_n(low,n+1,_st=0);
        fill_n(use,n+1, 0);
        rep(i,1,n+1) if(!dfn[i]) dfs(i,1,g);
        /*rep(i,1,n+1) for(auto j:g[i]) if(id[i]!=id[j.fi])
            bcc[id[i]].pb(id[j.fi]);
        */
		//rep(i, 1, n+1) V[id[i]].pb(i);
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


