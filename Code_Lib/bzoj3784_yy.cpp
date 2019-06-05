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

const int N = 50505, M = 303030;

int n, m;
vector<pii> g[N];

bool vis[N];
int sz[N];
int a[N * 16], cnta, st[N * 16], ed[N * 16], tp, bt, ma[20][N * 16], lg[N * 16];

int ans[M];

void dfssz(int c, int fa, int Sz, int &rt) {
	sz[c] = 1;
	rep(i, 0, sz(g[c])) {
		pii t = g[c][i];
		if(!vis[t.fi] && t.fi != fa) dfssz(t.fi, c, Sz, rt), sz[c] += sz[t.fi];
	}
	if(!rt && sz[c] * 2 > Sz) rt = c;
}
void dfs(int u, int fa, int dep) {
	a[++cnta] = dep;
	st[cnta] = tp;
	ed[cnta] = bt;
	rep(i, 0, sz(g[u])) {
		pii t = g[u][i];
		if(!vis[t.fi] && t.fi != fa) dfs(t.fi, u, dep + t.se);
	}
}
void dfs(int c) {
	int rt = 0; dfssz(c, 0, 0, rt); dfssz(c, 0, sz[c], rt = 0);
	vis[rt] = 1;
	c = rt;
	a[++cnta] = 0; tp = bt = cnta;
	st[cnta] = 0; ed[cnta] = -1;
	rep(i, 0, sz(g[c])) {
		pii t = g[c][i];
		if(!vis[t.fi]) {
			int v = t.fi;
			dfs(v, c, t.se);
			bt = cnta;
		}
	}
	rep(i, 0, sz(g[rt])) {
		pii t = g[rt][i];
		if(!vis[t.fi]) dfs(t.fi);
	}
}
int gao(int i, int j) {
	return a[i] > a[j] ? i : j;
}
int qry(int l, int r) {
	if(!(l <= r && l >= 1 && r <= cnta)) return 0;
	int i = lg[r - l + 1];
	return gao(ma[i][l], ma[i][r + 1 - (1 << i)]);
}
priority_queue<pair<pii, pii> > que;
void gao(int i, int st, int ed) {
	if(st > ed) return ;
	que.push(mp(mp(a[i] + a[qry(st, ed)], i), mp(st, ed)));
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n) {
		int u, v, w;
		cin >> u >> v >> w;
		g[u].pb(mp(v, w));
		g[v].pb(mp(u, w));
	}
	dfs(1);
	rep(i, 2, cnta + 1) lg[i] = lg[i >> 1] + 1;
	rep(i, 1, cnta + 1) ma[0][i] = i;
	rep(i, 1, lg[cnta] + 1) for(int j = 1; j + (1 << i) - 1 <= cnta; ++j) {
		ma[i][j] = gao(ma[i - 1][j], ma[i - 1][j + (1 << i >> 1)]);
	}
	rep(i, 1, cnta + 1) if(st[i] <= ed[i]) {
		gao(i, st[i], ed[i]);
	}
	rep(i, 1, m + 1) {
		pair<pii, pii> t = que.top();
		que.pop();
		ans[i] = t.fi.fi;
		int c = t.fi.se;
		int st = t.se.fi, ed = t.se.se;
		int mid = qry(st, ed);
		gao(c, st, mid - 1);
		gao(c, mid + 1, ed);
		cout << ans[i] << endl;
	}
	return 0;
}
