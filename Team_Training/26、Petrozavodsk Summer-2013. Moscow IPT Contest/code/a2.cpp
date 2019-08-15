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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 202020;

int n, m, col[N], L;
bool ok = 1;
pii e[N];
ll r[N], ha[N], r2[N], ha2[N];
vector<pair<ll, ll> > V;
vi g[N];
unordered_map<ll, bool> vis;

ll id(int u, int v) {
	if(u > v) swap(u, v);
	return u * 1ll * (n + 1) + v; 
}

int F(pair<ll, ll> x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

ll Rand() {
	return ((rand() * 1ll << 32) ^ (rand() * 1ll << 16) ^ rand());
}
void dfs(int u, int fa) {
	if(!ok) return ;
	col[u] = col[fa] + 1; L = max(col[u], L);
	for(auto v : g[u]) if(v != fa) {
		if(col[v]) {
			ok = 0;
			return ;
		}
		dfs(v, u);
	}
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	srand(time(0));
	cin >> n >> m;
	rep(i, 1, n + 1) r[i] = Rand(), r2[i] = Rand();
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		ha[u] ^= r[v];
		ha[v] ^= r[u];
		ha2[u] ^= r2[v];
		ha2[v] ^= r2[u];
		e[i] = mp(u, v);
	}
	rep(i, 1, n + 1) V.pb(mp(ha[i], ha2[i]));
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	rep(i, 1, m + 1) {
		int u = F(mp(ha[e[i].fi], ha2[e[i].fi])), v = F(mp(ha[e[i].se], ha2[e[i].se]));
		if(u == v) continue;
		int t = id(u, v);
		if(!vis[t]) {
			vis[t] = 1;
			g[u].pb(v), g[v].pb(u);
		}
	}
	rep(i, 1, sz(V) + 1) {
		if(sz(g[i]) > 2) ok = 0;
	}
	rep(i, 1, sz(V) + 1) {
		if(!col[i] && sz(g[i]) <= 1) {
			col[0] = L+1;
			dfs(i, 0);
		}
		if(!ok) break;
	}
	rep(i, 1, sz(V) + 1) if(!col[i]) ok = 0;
	if(ok) {
		cout << "DA" << endl;
		rep(i, 1, n + 1) cout << col[F(mp(ha[i], ha2[i]))] << " \n"[i == n];
	} else {
		cout << "NET" << endl;
	}
	return 0;
}
