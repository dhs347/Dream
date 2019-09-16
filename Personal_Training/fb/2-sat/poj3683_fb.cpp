#include<iostream>
#include<cstdio>
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

const int N = 1e5 + 7;

struct TwoSat {
    static const int N = ::N << 1;
    int dfn[N], low[N], id[N], st[N], _st, _, cc;
    vi g[N];
    int mark[N], n;
    void init(int _n) { per(i, 0, (n = _n << 1)) g[i].clear(); }
    int  new_node( ) { rep(i, 0, 2) g[n++].clear(); return n / 2 - 1; }
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
        for(auto t : g[c])
            if(!dfn[t])
                dfs(t, g), low[c] = min(low[c], low[t]);
            else if(!id[t])
                low[c] = min(low[c], dfn[t]);
        if(low[c] == dfn[c]){
            ++_;
            do{id[st[--_st]]=_;}while(st[_st] != c);
        }
    }
    void find(){
        fill_n(dfn, n, cc=0);
        fill_n(low, n, _st=0);
        fill_n(id, n, _=0);
        rep(i, 0, n) if(!dfn[i]) dfs(i, g);
        rep(i, 0, n) --id[i];
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
	
	int col[N], ans[N], tot;
	bool dfs(int u) {
        if (col[u] == -1) return 0;
        if (col[u] ==  1) return 1;
        ans[tot++] = u;
        col[u] = 1; col[u ^ 1] = -1;
        for (auto v : g[u]) if (!dfs(v)) return 0;
        return 0;
    }
	
    bool solve2() { // 构造字典序最小解
		for (int i = 0; i < n; i += 2) if (!col[i]) {
            tot = 0;
            if (!dfs(i)) {
                rep(j, 0, tot) col[ans[j]] = col[ans[j] ^ 1] = 0;
                if (!dfs(i ^ 1)) return 0;
            }
        }
        return 1;
    }
	
}  ts;

bool check(int l1, int r1, int l2, int r2) {
	return max(l1, l2) < min(r1, r2);
}

int n, h1[N], m1[N], h2[N], m2[N], t1[N], d[N], t2[N];

int main() {
	FI(a);
	//ios::sync_with_stdio(0);
	//cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 0, n) {
		scanf("%d:%d%d:%d%d", &h1[i], &m1[i], &h2[i], &m2[i], &d[i]);
		t1[i] = h1[i] * 60 + m1[i];
		t2[i] = h2[i] * 60 + m2[i];
	}
	ts.init(n);
	rep(i, 0, n) rep(j, i+1, n) {
		if (check(t1[i], t1[i] + d[i], t1[j], t1[j] + d[j])) ts.add_then(i, 0, j, 0);
		if (check(t1[i], t1[i] + d[i], t2[j] - d[j], t2[j])) ts.add_then(i, 0, j, 1);
		if (check(t2[i] - d[i], t2[i], t1[j], t1[j] + d[j])) ts.add_then(i, 1, j, 0);
		if (check(t2[i] - d[i], t2[i], t2[j] - d[j], t2[j])) ts.add_then(i, 1, j, 1);
	}
	if (!ts.solve()) {
		cout << "NO" << endl;
	}else {
		cout << "YES" << endl;
		rep(i, 0, n) if (!ts.mark[i]) {
			printf("%02d:%02d %02d:%02d\n", t1[i] / 60, t1[i] % 60, (t1[i] + d[i]) / 60, (t1[i] + d[i]) % 60);
		}else 
			printf("%02d:%02d %02d:%02d\n", (t2[i] - d[i]) / 60, (t2[i] - d[i]) % 60, t2[i] / 60, t2[i] % 60);
	}
	return 0;
}


