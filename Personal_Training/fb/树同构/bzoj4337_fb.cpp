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

const int N = 205, se = 233333, se2 = 1e9 + 9;
map<vi, int> M;
vi g[N];
int n, m, u, v, q, ans[N];

int get(int u, int fa) {
	int res = se;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i];
		if (v != fa) res = mul(res, get(v, u) ^ se2);
	}
	return res;
}

int main() {
	FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> m;
	rep(cas, 1, m+1) {
		cin >> n;
		rep(i, 0, n+1) g[i].clear();
		rep(i, 1, n+1) {
			cin >> u;
			if (u != 0) g[u].pb(i), g[i].pb(u);
		} 
		vi t;
		rep(i, 1, n+1) t.pb(get(i, 0));
		sort(all(t)); 
		if (M.find(t) == M.end()) M[t] = cas, ans[cas] = cas;
		else ans[cas] = M[t];
	} 
	rep(i, 1, m+1) cout << ans[i] << endl; 
	return 0;
}


