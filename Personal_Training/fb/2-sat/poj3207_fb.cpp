#include<iostream>
#include<vector>
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

// time : O(m)
// space : 2 * n
// index : [0, n)
// mark[i] :
//     i-th answer
//     i => [0, n)
// !!!! : init() before use
// 存在边 A -> B 则必有边 ~B -> ~A

const int N = 1e5 + 7;

struct TwoSat {
    static const int N = ::N << 1;
    int dfn[N], low[N], id[N], st[N], _st, _, cc;
    vi g[N];
    int mark[N], n;
    void init(int _n) { per(i, 0, (n = _n << 1)) g[i].clear(); }
    int  new_node( ) { rep(i, 0, 2) g[n++].clear(); return n >> 1; }
    /// optionals begin
    void addedge(int a, int va, int b, int vb) { // va 选了 vb 必选  
		a = a << 1 | va; b = b << 1 | vb;
        g[a].pb(b); g[b ^ 1].pb(a ^ 1);
	}
    void add_set(int a, int va) { a = a << 1 | va; g[a ^ 1].pb(a); } // va 必选   
    
    void add_then(int a, int va, int b, int vb) { // va 和 vb 不能同时取
    	addedge(a, va, b, vb ^ 1); 
    }
    void add_or (int a, int va, int b, int vb) { // va 和 vb 不能同时不取 
    	addedge(a, va ^ 1, b, vb);
    }
    void add_xor(int a, int va, int b, int vb) { // va 和 vb 同时取或同时不取
        addedge(a, va, b, vb);
        addedge(b, vb, a, va);
    }
    // 需要 sz(vu) 个额外的 dp 变量
    void add_at_most_one(vector<pii> vu) {
        int pre = -1;
        rep(i, 0, sz(vu)) {
            int a = vu[i].fi, va = vu[i].se;
            int dpi = new_node();
            add_then(a, va, dpi, 1);
            if (i) {
                add_then(pre, 1, dpi, 1);
                add_then(pre, 1, a, va ^ 1);
            }
            pre = dpi;
        }
    }
    // optionals end

    void dfs(int c, vi g[]){
        dfn[c] = low[c] = ++cc;
        st[_st++] = c;
        //for(auto t : g[c])
       	rep(i, 0, sz(g[c])) {
		    int t = g[c][i];
			if(!dfn[t])
                dfs(t, g), low[c] = min(low[c], low[t]);
            else if(!id[t])
                low[c] = min(low[c], dfn[t]);
		}
        if(low[c] == dfn[c]){
            ++_;
            do{id[st[--_st]]=_;}while(st[_st] != c);
        }
    }
    void find(){
        fill_n(dfn,n,cc=0);
        fill_n(low,n,_st=0);
        fill_n(id,n,_=0);
        rep(i,0,n) if(!dfn[i]) dfs(i, g);
        rep(i,0,n) --id[i];
        return;
    }
    bool solve() { // 构造任意解 
        find();
        for (int i = 0; i < n; i += 2) {
            if (id[i] == id[i + 1]) return 0;
            mark[i >> 1] = (id[i] > id[i + 1]);
        }
        return 1;
    }
}  ts;

int T, n, m, u[N], v[N], id[N], p[N];

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	T = 1;
	rep(cas, 0, T) {
		cin >> n >> m;
		rep(i, 1, m+1) cin >> u[i] >> v[i];
		ts.init(n);
		rep(i, 1, m+1) {
			if (id[u[i]] % n + 1 == id[v[i]]) continue;
			rep(j, i+1, m+1) {
				if (id[u[j]] % n + 1 == id[v[j]]) continue;
				if (id[u[i]] < id[u[j]]) {
					if (id[v[i]] < id[v[j]] && id[v[i]] > id[u[j]]) ts.add_then(i-1, 1, j-1, 1), ts.add_then(i-1, 0, j-1, 0); 
				}
				if (id[u[i]] > id[u[j]]) {
					if (id[v[j]] < id[v[i]] && id[v[j]] > id[u[i]]) ts.add_then(i-1, 1, j-1, 1), ts.add_then(i-1, 0, j-1, 0);
				}
 			}
		}
		if (ts.solve()) cout << "YES" << endl;
		else cout << "NO" << endl;
	}
	return 0;
}




