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


int n, fa[N], d[N], a[300][300], u, v, uu, vv, l, r, mid, ans;
vector<pair<int, pii> > e;
int get(int x) {
	if (x == fa[x]) return x;
	int t = fa[x];
	fa[x] = get(fa[x]);
	d[x] ^= d[t];
	return fa[x];
}

bool check(int l1, int l2) {
	ts.init(n);
//	rep(i, 0, sz(e)) {
//		if (e[i].fi > e[l1].fi) ts.add_then(e[i].se.fi, 1, e[i].se.se, 1);
//		if (e[i].fi > e[l2].fi) ts.add_then(e[i].se.fi, 0, e[i].se.se, 0);
//	} 
	rep(i, l1+1, sz(e)) ts.add_then(e[i].se.fi, 1, e[i].se.se, 1);
	rep(i, l2+1, sz(e)) ts.add_then(e[i].se.fi, 0, e[i].se.se, 0);
	return ts.solve();
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	if (n <= 2) {
		cout << 0 << endl;
		return 0;
	}
	rep(i, 0, n) rep(j, i+1, n) {
		cin >> a[i][j];
		e.pb(mp(a[i][j], mp(i, j)));
	}
	sort(all(e));
	rep(i, 0, n) fa[i] = i;
	ans = INT_MAX;
	per(i, 0, sz(e)) {
		u = e[i].se.fi; v = e[i].se.se;
		uu = get(u); vv = get(v);
		if (uu != vv || (d[u] ^ d[v] ^ 1) == 1) {
			l = -1; r = i - 1;
			while (l <= r) {
				mid = l + r >> 1;
				if (check(i, mid)) ans = min(ans, e[i].fi + (mid >= 0 ? e[mid].fi : 0)), r = mid - 1;
				else l = mid + 1;
			}
			if (uu != vv) fa[uu] = vv, d[uu] = d[u] ^ d[v] ^ 1;
		}
		if (uu == vv && (d[u] ^ d[v] ^ 1) == 1) break;
	} 
	cout << ans << endl;
	return 0;
}


