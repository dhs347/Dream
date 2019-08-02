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

const int N = 2005, se = 233333, se2 = 1e9 + 9;
unordered_map<int, int> dp[N][13], ans;
vi g[N];
int n, m, u, v, q;

void dfs(int u, int fa) {
	int o = 0; 
	unordered_map<int, int> M[2][13];
	M[0][1][se] = 1;
	for (auto v : g[u]) if (v != fa){
		dfs(v, u);
		rep(i, 1, 13) rep(j, 1, 13 - i) {
			for (auto t1 : M[o][i])
				for (auto t2 : dp[v][j]) {
					(M[o^1][i+j][mul(t1.fi, t2.fi ^ se2)] += mul(t1.se, t2.se)) %= P;
				}
		}
		rep(i, 1, 13) for (auto t1 : M[o][i]) (M[o^1][i][t1.fi] += t1.se) %= P;
		rep(i, 1, 13) M[o][i].clear(); 
		o ^= 1;
	}
	rep(i, 1, 13) dp[u][i] = M[o][i];
}

int get(int u, int fa) {
	int res = se;
	for (auto v : g[u]) if(v != fa) {
		res = mul(res, get(v, u) ^ se2);
	}
	return res;
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	rep(i, 1, n) {
		cin >> u >> v; 
		g[u].pb(v);
		g[v].pb(u);
	} 
	dfs(1, 0);
	cin >> q;
	rep(cas, 0, q) {
		cin >> m; vi V;
		rep(i, 1, m+1) g[i].clear();
		rep(i, 1, m) {
			cin >> u >> v;
			g[u].pb(v);
			g[v].pb(u);
		}
		int sum = 0;
		rep(i, 1, m+1) V.pb(get(i, 0));
		sort(all(V)); V.erase(unique(all(V)), V.end());
		for (auto u : V) {
			auto t = ans.find(u);
			if (t == ans.end()) {
				int w = 0;
				rep(i, 1, n+1) if (dp[i][m].find(u) != dp[i][m].end()) w = add(w, dp[i][m][u]);
				ans[u] = w;
				sum = add(sum, w);
			}else sum = add(sum, (*t).se);
		}
		cout << sum << endl;
	}
	return 0;
}


