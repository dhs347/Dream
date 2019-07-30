#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 50505, M = 33;

int n, k, Gcd[N], pw[N], val[N], cnt[M][N], val2[N], Dep[N];
ll ans;
string s;
vi g[N], ks, vec[N];

void exgcd(ll a, ll b, ll &x, ll &y){
	if (!b) { x = 1; y = 0; return;}
	exgcd(b, a % b, y, x);
	y -= a / b * x;
}
ll Inv(ll a, ll mod){
	ll x = 0, y = 0;
	exgcd(a, mod, x, y);
	x %= mod;
	return x < 0 ? x + mod : x;
}

// id starts from 1
namespace Cen {
	const int N = ::N;
	bool vis[N]; int sz[N];
	void dfssz(int c,int fa,int Sz,int &rt){
		sz[c] = 1;
		for(auto t : g[c]) if(!vis[t]&&t!=fa) dfssz(t,c,Sz,rt) , sz[c]+=sz[t];
		if(!rt && sz[c]*2>Sz) rt=c;
	}
	void dfs(int u, int fa, int dep, int tp) {
		val[u] = (val[fa] + (s[u - 1] - '0') * pw[dep]) % k;
		val2[u] = (val2[fa] * 10 + s[u - 1] - '0') % k;
		Dep[u] = Dep[fa] + 1;
		vec[tp].pb(u);
		rep(i, 0, sz(ks)) ++cnt[i][val[u] % ks[i]];
		for(auto v : g[u]) if(v != fa && !vis[v]) dfs(v, u, dep + 1, tp);
	}
	void gao(int v) {
		int a = pw[Dep[v]], b = val2[v] ? k - val2[v] : 0, p = k, g = __gcd(a, p);
		if(b % g) return ;
		a /= g, b /= g, p /= g;
		a = Inv(a, p);
		int x = b * 1ll * a % p;
		int pos = lower_bound(all(ks), p) - ks.begin();
		ans += cnt[pos][x];
	}
	void dfs(int c){
		int rt=0;dfssz(c,0,0,rt);dfssz(c,0,sz[c],rt=0);
		vis[rt] = true; val[rt] = 0; val2[rt] = (s[rt - 1] - '0') % k; Dep[rt] = 1;
		for(auto u : g[rt]) if(!vis[u]) {
			vec[u].clear();
			dfs(u, rt, 0, u);
		}
		rep(i, 0, sz(ks)) ++cnt[i][0];
		for(auto u : g[rt]) if(!vis[u]) {
			for(auto v : vec[u]) rep(i, 0, sz(ks)) --cnt[i][val[v] % ks[i]];
			for(auto v : vec[u]) gao(v);
			for(auto v : vec[u]) rep(i, 0, sz(ks)) ++cnt[i][val[v] % ks[i]];
		}
		gao(rt);
		for(auto u : g[rt]) if(!vis[u]) {
			for(auto v : vec[u]) rep(i, 0, sz(ks)) --cnt[i][val[v] % ks[i]];
		}
		rep(i, 0, sz(ks)) --cnt[i][0];
		for(auto t : g[rt]) if(!vis[t]) dfs(t);
	}
	void init() {
		fill_n(vis + 1, n, 0);
	}
};

void solve() {
	cin >> n >> k >> s;
	rep(i, 1, n + 1) g[i].clear();
	ks.clear(); Cen::init();
	rep(i, 1, n) {
		int u, v; cin >> u >> v;
		g[u].pb(v);
		g[v].pb(u);
	}
	pw[0] = 1; rep(i, 1, n + 1) pw[i] = pw[i - 1] * 10 % k;
	Gcd[0] = 1; int now = k; ks.pb(k);
	rep(i, 1, n + 1) {
		int t = __gcd(10, now);
		now /= t;
		Gcd[i] = Gcd[i - 1] * t;
		if(t > 1) ks.pb(k / Gcd[i]);
	}
	reverse(all(ks));
	ans = 0; Cen::dfs(1);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
