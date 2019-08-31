#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(c) cout << #c << " = " << c << endl
#define dd(c) cout << #c << " = " << c << " "
#define endl '\n'
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n;
int dp[N], ne[N];

struct P {
	int x, y, ind, rka, rkb;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	void read() {
		cin >> x >> y;
	}
}p, q, ps[N];

vector<P> qs[2];
vi ans[2];
struct Fenwick {
#define lb(x) ((x)&-(x))
	int a[N];
	void init() {
		fill_n(a, n + 1, 0);
	}
	void _upd(int &a, int &b) {
		if(!b) return ;
		if(!a || dp[a] < dp[b] || (dp[a] == dp[b] && a > b)) return a = b, void();
	}
	void upd(int p, int c) {
		for(; p <= n; p += lb(p)) _upd(a[p], c);
	}
	int qry(int p) {
		int ans = 0;
		for(; p; p ^= lb(p)) _upd(ans, a[p]);
		return ans;
	}
}fw;
ll det(P a, P b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}

ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
void print(vi &ans) {
	cout << sz(ans) << endl;
	for(auto u : ans) cout << u << endl;
}
bool cmp(P a, P b) {
	return det(a - p, b - p) < 0;
}
bool cmp2(P a, P b) {
	return det(a - q, b - q) > 0;
}
bool cmp3(P a, P b) {
	if(a.rka != b.rka) return a.rka < b.rka;
	return a.rkb > b.rkb;
}
void solve(vector<P> &ps, vi &ans) {
	fw.init();
	sort(all(ps), cmp);
	rep(i, 0, sz(ps)) {
		if(i == 0) ps[i].rka = 1;
		else ps[i].rka = ps[i - 1].rka + (det(ps[i] - p, ps[i - 1] - p) != 0);
	}
	sort(all(ps), cmp2);
	rep(i, 0, sz(ps)) {
		if(i == 0) ps[i].rkb = 1;
		else ps[i].rkb = ps[i - 1].rkb + (det(ps[i] - q, ps[i - 1] - q) != 0);
	}
	sort(all(ps), cmp3);
	for(auto u : ps) {
		int v = fw.qry(u.rkb - 1);
		if(v) dp[u.ind] = dp[v] + 1, ne[u.ind] = v;
		else dp[u.ind] = 1, ne[u.ind] = 0;
		fw.upd(u.rkb, u.ind);
	}
	int now = fw.qry(n);
	while(now) ans.pb(now), now = ne[now];
}
void solve() {
	p.read(); q.read();
	cin >> n;
	rep(i, 1, n + 1) ps[i].read(), ps[i].ind = i;
	rep(o, 0, 2) qs[o].clear(), ans[o].clear();
	rep(i, 1, n + 1) qs[det(p, q, ps[i]) > 0].pb(ps[i]);
	rep(o, 0, 2) {
		if(o) swap(p, q);
		solve(qs[o], ans[o]);
	}
	if(sz(ans[0]) > sz(ans[1])) swap(ans[0], ans[1]);
	if(sz(ans[0]) == sz(ans[1])) {
		bool ok = 1;
		rep(i, 0, sz(ans[0])) if(ans[0][i] != ans[1][i]) {
			print(ans[ans[0][i] > ans[1][i]]);
			ok = 0;
			break;
		}
		if(ok) print(ans[0]);
	} else {
		print(ans[1]);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
