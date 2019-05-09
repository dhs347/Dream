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
typedef double db;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int, int> pii;
typedef vector<int> vi;
const int P = 1e9 + 7;
int add(int a, int b) {if((a += b) >= P) a -= P; return a < 0 ? a + P : a;}
int mul(int a, int b) {return 1ll * a * b % P;}
int kpow(int a, int b) {int r=1;for(;b;b>>=1,a=mul(a,a)) {if(b&1)r=mul(r,a);}return r;}
//----

const int N = 1e5 + 6;
int d[N], n, Q, u, v, ans[N];
vector<vector<pii> > q;
vector<vi> g;

inline void bfs(int x, vector<vi> &g) {
	d[x] = 0;
	queue<int> q; q.push(x);
	while (!q.empty()) {
		int u = q.front(); q.pop();
		rep(i, 0, sz(g[u])) {
			int v = g[u][i];
			if (d[v] > d[u] + 1) {
				d[v] = d[u] + 1;
				q.push(v);
			}
		}
	}
}

inline void solve(int n, vector<vi> &g, vector<vector<pii> > &q) {
	if (n <= 3) {
		rep(i, 0, n) rep(j, 0, sz(q[i])) ans[q[i][j].se] = 1;
		return;
	}
	int t = pw(30), l, r, w = n - 2;
	rep(i, 0, n) {
		rep(j, 0, sz(g[i])) {
			int v = g[i][j];
			if (v < i) continue;
			if (abs(v - i - 1 - w / 2) < t && v - i - 1 < w && v - i - 1 > 0) {
				t = abs(v - i - 1 - w / 2);
				l = i; r = v;
			}
		}
	}
	vector<vi> g1, g2;
	vector<vector<pii> > q1, q2;
	g1.resize(r - l + 1);
	q1.resize(r - l + 1);
	rep(i, l, r + 1) {
		rep(j, 0, sz(g[i])) if (g[i][j] >= l && g[i][j] <= r) {
			g1[i - l].pb(g[i][j] - l);
		}
		rep(j, 0, sz(q[i])) if (q[i][j].fi >= l && q[i][j].fi <= r) {
			q1[i - l].pb(mp(q[i][j].fi - l, q[i][j].se));
		}
	} 
	g2.resize(l + 1 + n - r);
	q2.resize(l + 1 + n - r);
	rep(i, 0, l + 1) {
		rep(j, 0, sz(g[i])) if (g[i][j] <=l || g[i][j] >= r) {
			g2[i].pb(g[i][j] <= l ? g[i][j] : g[i][j] - r + l + 1);
		}
		rep(j, 0, sz(q[i])) if (q[i][j].fi <= l || q[i][j].fi >= r) {
			q2[i].pb(mp(q[i][j].fi <= l ? q[i][j].fi : q[i][j].fi - r + l + 1, q[i][j].se));
		}
	}
	rep(i, r, n) {
		rep(j, 0, sz(g[i])) if (g[i][j] <= l || g[i][j] >= r) {
			g2[i - r + l + 1].pb(g[i][j] <= l ? g[i][j] : g[i][j] - r + l + 1);
		}
		rep(j, 0, sz(q[i])) if (q[i][j].fi <= l || q[i][j].fi >= r) {
			q2[i - r + l + 1].pb(mp(q[i][j].fi <= l ? q[i][j].fi : q[i][j].fi - r + l + 1, q[i][j].se));
		}
	}
	rep(i, 0, n) d[i] = pw(30);
	bfs(l, g);
	rep(i, 0, n) {
		rep(j, 0, sz(q[i])) ans[q[i][j].se] = min(ans[q[i][j].se], d[i] + d[q[i][j].fi]);
	}
	rep(i, 0, n) d[i] = pw(30);
	bfs(r, g);
	rep(i, 0, n) {
		rep(j, 0, sz(q[i])) ans[q[i][j].se] = min(ans[q[i][j].se], d[i] + d[q[i][j].fi]);
	}
	solve(r - l + 1, g1, q1);
	solve(l + 1 + n - r, g2, q2);
	return;
}

int main() {
	//freopen("a.in","r",stdin);
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	//cout << setiosflags(ios::fixed);
	//cout << setprecision(2);
	cin >> n;
	g.resize(n);
	q.resize(n);
	rep(i, 1, n - 3 + 1) {
		cin >> u >> v;
		u--;v--;
		g[u].pb(v);
		g[v].pb(u);
	}
	rep(i, 0, n) {
		g[i].pb(i + 1 >= n ? 0 : i + 1);
		g[i].pb(i - 1 < 0 ? n-1 : i - 1);
	}
	cin >> Q;
	rep(i, 0, Q) {
		cin >> u >> v;
		u--;v--;
		if (u == v) ans[i] = 0;
		else if (u == (v + 1) % n || v == (u + 1) % n) ans[i] = 1;
		else {
			q[u].pb(mp(v, i));
			ans[i] = pw(30);
		}
	}	
	solve(n, g, q);
	rep(i, 0, Q) cout << ans[i] << endl;
	return 0;
}


