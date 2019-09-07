#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1e6 + 7;

int n, q, a[N], par[N], dep[N], st[N], ed[N], dfn;
ll ans[N];
vi g[N];
vector<pair<int, pii> > vec[N];
int nn;

struct FW {
	static const int N = ::N;
	ll sum[N];
#define lb(x) ((x)&-(x))
	void upd(int p, int c) {
		for(; p <= n; p += lb(p)) sum[p] += c;
	}
	ll _qry(int p) {
		ll r = 0;
		for(; p; p ^= lb(p)) r += sum[p];
		return r;
	}
	ll qry(int l, int r) {
		return _qry(r) - _qry(l - 1);
	}
}fw;

void add(int v, int i, int k) {
	//dd(v), dd(i), de(k);
	int l = dep[v], r = min(dep[v] + k, nn);
	vec[r].pb(mp(i, mp(st[v], ed[v])));
//	dd(l), dd(r), dd(i), dd(st[v]), de(ed[v]);
	vec[l - 1].pb(mp(-i, mp(st[v], ed[v])));
}
void dfs(int u, int fa) {
	st[u] = ++dfn;
	par[u] = fa;
	dep[u] = dep[fa] + 1;
	nn = max(nn, dep[u]);
	for(auto v : g[u]) if(v != fa) dfs(v, u);
	ed[u] = dfn;
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	srand(time(0));
	n = 1e6;
	//cin >> n;
	rep(i, 1, n + 1) {
		a[i] = rand();
//		cin >> a[i];
	}
	rep(v, 2, n + 1) {
		int u = rand() % (v - 1) + 1;
		g[u].pb(v);
		g[v].pb(u);
	}
	dfs(1, 0);
	q = 5000;
	//cin >> q;
	rep(i, 1, q + 1) {
		int v, k; 
		v = rand() % n + 1, k = 100;
		//cin >> v >> k; 
		int u = v;
		while(k >= 0 && v) {
			if(u == v) {
				add(v, i, k);
			} else {
				add(v, i, k);
				if(k) add(u, -i, k - 1);
			}
			u = v, v = par[v], --k;
		}
	}
	vi que; que.pb(1);
	rep(i, 0, sz(que)) {
		int u = que[i]; 
		for(auto v : g[u]) if(v != par[u]) que.pb(v);
	}
//	de(sz(que));
	rep(i, 0, sz(que)) {
		int u = que[i];
		fw.upd(st[u], a[u]);
		if(i == sz(que) - 1 || dep[que[i]] != dep[que[i + 1]]) {
			int d = dep[u];
			for(auto t : vec[d]) {
				auto ret = fw.qry(t.se.fi, t.se.se);
				int o = t.fi > 0 ? 1 : -1;
				ans[abs(t.fi)] += o * ret;
			}
		}
	}
//	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
