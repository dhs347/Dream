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

int n, m, L, col[N];
bool vis[N], ok = 1;
vi g[N];
vector<pii> vec;

void dfs(int u) {
	vec.pb(mp(sz(g[u]), u));
	vis[u] = 1;
	for(auto v : g[u]) if(!vis[v]) dfs(v);
}

void gao(int u, int c) {
	col[u] = c; L = max(L, c);
	for(auto v : g[u]) if(!col[v]) gao(v, c + 1);
}
void gao(int u) {
	if(!ok) return ;
	for(auto v : g[u]) {
		int nc = col[u], pc = (nc == L ? L + 1 : L);
		if(col[v]) {
			if(col[v] != pc) ok = 0;
		} else {
			col[v] = pc;
			gao(v);
		}
	}
}

void solve(int u) {
	vec.clear(); dfs(u);
	int tot = 0; for(auto v : vec) tot += v.fi;
	sort(all(vec));
	if(tot == 2 * (sz(vec) - 1)) {
		gao(vec[0].se, ++L);
	} else {
		int cnt = 0, p = 0;
		rep(i, 1, sz(vec)) if(vec[i].fi != vec[i - 1].fi) ++cnt, p = i;
		if(cnt > 1) { ok = 0; return ; }
		if(p == 0) {
			if(sz(vec) % 2 == 0 && vec[0].fi == sz(vec) / 2) {
				col[vec[0].se] = ++L; 
				gao(vec[0].se);
				++L;
			} else {
				ok = 0; return ;
			}
		} else {
			if(vec[0].fi == sz(vec) - p && vec.back().fi == p) {
				col[vec[0].se] = ++L; 
				gao(vec[0].se);
				++L;
			} else {
				ok = 0; return ;
			}
		}
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, m + 1) {
		int u, v; cin >> u >> v;
		g[u].pb(v), g[v].pb(u);
	}
	rep(i, 1, n + 1) {
		if(!col[i]) solve(i);
		if(!ok) break;
	}
	if(ok) {
		cout << "DA" << endl;
		rep(i, 1, n + 1) cout << col[i] << " \n"[i == n];
	} else {
		cout << "NET" << endl;
	}
	return 0;
}
