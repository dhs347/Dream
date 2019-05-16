#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define all(a) a.begin(), a.end()
#define pw(x) (1ll <<(x))
#define endl "\n"
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n;
ll ans;
vector<pii> g[N];

bool vis[N]; int sz[N];
vector<pii> vec[N];
map<int, int> cnt;
map<pii, int> cc;

void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	rep(i, 0, sz(g[c])) {
		int t = g[c][i].fi;
		if(!vis[t] && t != fa) dfssz(t, c, Sz, rt), sz[c] += sz[t];
	}
	if(!rt && sz[c] * 2 > Sz) rt = c;
}
void dfs(int u, int fa, int val, int rt) {
	vec[rt].pb(mp(val, cnt[val] > 0));
	cnt[val]++;
	rep(i, 0, sz(g[u])) {
		int v = g[u][i].fi;
		if(!vis[v] && v != fa) dfs(v, u, val + g[u][i].se, rt);
	}
	cnt[val]--;
}
void dfs(int c) {
	int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
	rep(i, 0, sz(g[rt])) {
		int v = g[rt][i].fi;
		if(!vis[v]) {
			cnt.clear();
			vec[v].clear();
			dfs(v, rt, g[rt][i].se, v);
		}
	}
	cc.clear();
	rep(i, 0, sz(g[rt])) {
		int v = g[rt][i].fi;
		if(!vis[v]) {
			rep(j, 0, sz(vec[v])) {
				int x = vec[v][j].fi, y = vec[v][j].se;
				if(x == 0) {
					ans += cc[mp(0, 0)] + cc[mp(0, 1)];
					if(y == 1) ans++;
				} else if(y) {
					ans += cc[mp(-x, 0)] + cc[mp(-x, 1)];
				} else {
					ans += cc[mp(-x, 1)];
				}
			}
			rep(j, 0, sz(vec[v])) cc[vec[v][j]]++;
		}
	}
	rep(i, 0, sz(g[rt])) {
		int t = g[rt][i].fi;
		if(!vis[t]) dfs(t);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		if(w == 0) w = -1;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	dfs(1);
	cout << ans << endl;
	return 0;
}
