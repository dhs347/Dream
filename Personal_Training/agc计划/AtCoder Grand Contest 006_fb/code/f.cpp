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

const int N = 1e5 + 8;
bool ok;
int vis[N], n, m, u, v;
ll use[N], ans;
vi g[N], gg[N], tmp;

int inc(int x) {
	x++;
	if (x == 4) x = 1;
	return x;
}

int dec(int x) {
	x--;
	if (x == 0) x = 3;
	return x;
}

void dfs(int u) {
	tmp.pb(u);
	for (auto v : g[u]) {
		if (!vis[v]) {
			vis[v] = inc(vis[u]);
			dfs(v);
		}else {
			if (vis[v] != inc(vis[u])) {
				ok = 0;
			}
		}
	}
	for (auto v : gg[u]) {
		if (!vis[v]) {
			vis[v] = dec(vis[u]);
			dfs(v);
		}else {
			if (vis[v] != dec(vis[u])) {
				ok = 0;
			}
		}
	}
}

int main() {
	//FI(a);
	ios::sync_with_stdio(0);
	cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n >> m;
	rep(i, 1, m+1) {
		cin >> u >> v;
		g[u].pb(v);
		gg[v].pb(u);
	} 
	rep(i, 1, n+1) if (!vis[i]) {
		ok = 1; tmp.clear(); vis[i] = 1;
		dfs(i);
		//de(ok);de(ans);
		if (!ok) {
			ans += 1ll * sz(tmp) * sz(tmp);
		}else {
			rep(i, 1, 4) use[i] = 0;
			for (auto u : tmp) use[vis[u]]++;
			rep(i, 1, 4) ok &= use[i] > 0;
			//de(use[1]);
			//de(use[2]);
			//de(use[3]);
			if (ok) ans += use[1] * use[2] + use[2] * use[3] + use[3] * use[1];
			else {
				int t = 0;
				for (auto u : tmp) ans += sz(g[u]);
			}
		}
	}
	cout << ans << endl;
	return 0;
	
}


