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
const int P = 1e9 + 7;
//ll rnd(ll l, ll r) { mt19937 gen(rand()); RR dis(l, r); return dis(gen); }
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----



template<class T>
struct Dinic{
    const static int N = 10101 , M = N * 10;
    int s , t , n , h[N] , cur[N] , lv[N] , q[N] , e , ne[M] , to[M];
    T cap[M] , flow;
    void liu(int u,int v,T w){ to[e] = v;ne[e] = h[u];cap[e] = w;h[u] = e++;}
    void link(int u,int v,T w){ liu(u , v , w);liu(v , u , 0);}
    void ini(int _n = N) { fill(h , h + (n=_n) , -1);e = 0;}
    bool bfs(){
        int L = 0 , R = 0;
        fill(lv , lv + n , -1);
        lv[q[R++] = s] = 0;
        while(L < R && !~lv[t]){
            int c = q[L++];
            for(int k = h[c]; ~k ; k = ne[k])
                if(cap[k] > 0 && !~lv[to[k]]) 
                    lv[q[R++] = to[k]] = lv[c] + 1;
        }
        return ~lv[t];
    }
    T dfs(int c,T mx){
        if(c == t) return mx;
        T ret = 0;
        for(int &k = cur[c]; ~k; k = ne[k]){
            if(lv[to[k]] == lv[c] + 1 && cap[k] > 0){
                T flow = dfs(to[k] , min(mx , cap[k]));
                ret += flow;cap[k] -= flow , cap[k^1] += flow;mx -= flow;
                if(!mx) return ret;
            }
        }
        lv[c] = -1;
        return ret;
    }
    T run(int _s,int _t){
        s = _s , t = _t;
        flow = 0;
        while(bfs()){
            copy(h , h + n , cur);
            flow += dfs(s, ~0U>>1);
        }
        return flow;
    }
};

Dinic<int> G;
set<int> S;
struct GHT{
	static const int N = 1e5 + 100, M = 17; // (1 << M) > n
	int id[N], tmp[N], n, f[N][M], h[N][M], dep[N];
	vector<pii> g[N];
	void ini(int _n) { n = _n; G.ini(n + 5); rep(i, 1, n+1) id[i] = i, g[i].clear(); }
	void link(int u, int v, int w) { G.link(u, v, w); G.link(v, u, w);}
	void solve(int l, int r) {
		if (l == r) return;
		int s = id[l], t = id[l+1];
		for(int i = 0; i < G.e; i += 2) G.cap[i] += G.cap[i+1], G.cap[i+1] = 0; 
		int w = G.run(s, t);  S.insert(w);
		g[s].pb(mp(t, w));
		g[t].pb(mp(s, w));
		int cl = l, cr = 0;
		rep(i, l, r+1) {
			if (G.lv[id[i]] != -1) id[cl++] = id[i];
			else tmp[cr++] = id[i];
		}
		rep(i, 0, cr) id[cl + i] = tmp[i];
		solve(l, cl - 1);
		solve(cl, r);
	}
	
	void dfs(int u, int fa) {
		dep[u] = dep[fa] + 1;
		for (auto v : g[u]) if (v.fi != fa) {
			f[v.fi][0] = u; h[v.fi][0] = v.se;
			rep(i, 1, M) {
				f[v.fi][i] = f[f[v.fi][i-1]][i-1];
				h[v.fi][i] = min(h[v.fi][i-1], h[f[v.fi][i-1]][i-1]);
			} 
			dfs(v.fi, u);
		}
	}
	
	void build() { solve(1, n); dfs(1, 0); }
	
	int get(int u, int v) { // зЂвт long long 
		int res = pw(30);
		if (dep[u] < dep[v]) swap(u, v);
		per(i, 0, M) if (dep[f[u][i]] >= dep[v]) res = min(res, h[u][i]), u = f[u][i]; 
		per(i, 0, M) if (f[u][i] != f[v][i]) res = min(res, min(h[u][i], h[v][i])), u = f[u][i], v = f[v][i];
		if (u != v) res = min(res, min(h[u][0], h[v][0]));
		return res;
	}
	
} tr;

int n, m, u, v, w, q, x, T;

int main() {
	FI(a); 
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	T = 1; 
	rep(cas, 0, T) { 
		cin >> n >> m; 
		tr.ini(n);
		rep(i, 1, m+1) {
			cin >> u >> v >> w;
			tr.link(u, v, w);
		} 
		S.clear();
		tr.build();
		cout << sz(S) << endl;
	}
	return 0;
}

