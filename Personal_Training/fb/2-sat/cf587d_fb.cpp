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
 
const int N = 3e5 + 7;
 
struct TwoSat {
    static const int N = ::N << 1;
    int dfn[N], low[N], id[N], st[N], _st, _, cc;
    vi g[N];
    int mark[N], n;
    void init(int _n) { per(i, 0, (n = _n << 1)) g[i].clear(); }
    int  new_node( ) { rep(i, 0, 2) g[n++].clear(); return (n >> 1) - 1; }
    /// optionals begin
    void addedge(int a, int va, int b, int vb) { // va 选了 vb 必选  
		a = a << 1 | va; b = b << 1 | vb;
        g[a].pb(b); g[b ^ 1].pb(a ^ 1);
	}
    void add_set(int a, int va) { a = a << 1 | va; g[a ^ 1].pb(a); } // va 必选   
    void del(int a, int va) { a = a << 1 | va; g[a ^ 1].pop_back(); }
    
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
            addedge(a, va, dpi, 1);
            if (i) {
                addedge(pre, 1, dpi, 1);
                addedge(pre, 1, a, va ^ 1);
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
 
int n, m;
pair<pii, int> p[N];
pii e[N];
vector<pii> ban[N];
int cnt[N], used[N];
vi ans;
 
bool check(int x) {
	rep(i, 0, m) if(p[i].fi.se > x) ts.add_set(i, 0);
	int re = ts.solve();
	rep(i, 0, m) if(p[i].fi.se > x) ts.del(i, 0);
	return re;
}
 
int main() {
	cin >> n >> m;
	rep(i, 0, m) {
		cin >> e[i].fi >> e[i].se >> p[i].fi.fi >> p[i].fi.se;
		p[i].se = i;
	}
	sort(p, p+m);
	ts.init(m);
	memset(cnt, -1, sizeof(cnt));
	rep(i, 0, m) {
		int id = p[i].se, u = e[id].fi, v = e[id].se;
		ban[u].pb(mp(i, 1));
		ban[v].pb(mp(i, 1));
	}
	rep(i, 1, n+1) ts.add_at_most_one(ban[i]);
	
 
	for(int i = 0, j = 0; i < m; i = j) {
		while(j < m && p[i].fi.fi == p[j].fi.fi) j++;
		int c = p[i].fi.fi;
		rep(k, i, j) {
			int u = e[p[k].se].fi, v = e[p[k].se].se;
			if(cnt[u] == j-1) return 0 * printf("No\n");
			else if(cnt[u] >= i) {
				if(used[u]) return 0 * printf("No\n");
				used[u] = c;
				ts.add_then(cnt[u], 0, k, 0);
				cnt[u] = j-1;		
			}else cnt[u] = k;
 
			if(cnt[v] == j-1) return 0 * printf("No\n");
			else if(cnt[v] >= i) {
				if(used[v]) return 0 * printf("No\n");
				used[v] = c;
				ts.add_then(cnt[v],0,k,0);
				cnt[v] = j-1;
			}else cnt[v] = k;
		}
	}
 
	int l = 0, r = pw(30);
	while(l < r) {
		int mid = (l + r) >> 1;
		if(check(mid)) r = mid;
		else l = mid + 1;
	}
	rep(i, 0, m) if (p[i].fi.se > l) ts.add_set(i, 0);
	if(!ts.solve()) return 0 * printf("No\n");
	printf("Yes\n");
	rep(i, 0, m) if(ts.mark[i]) ans.pb(p[i].se);
	printf("%d %d\n", l, sz(ans));
	sort(all(ans));
	for(int x : ans) printf("%d ", x+1);
	return 0;
}
 
