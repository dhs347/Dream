#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 2020;
const ll inf = 4e18;

int n, m;
int pos[N];
ll ma, mi;
struct P {
	int x, y, u, v, ind;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	bool operator == (const P &c) const {
		return x == c.x && y == c.y;
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	void print() {
		dd(x), de(y);
	}
}p[N], l[N * N];
vector<P> qs;
ll det(P a, P b) {
	return a.x * 1ll * b.y - a.y * 1ll * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
bool cmp(const P &x, const P &y) {
	return det(x, y) < 0;
}
bool cmp2(const P &x, const P &y) {
	return x.y < y.y;
}
void convex() {
	qs.clear();
	sort(p + 1, p + 1 + n);
	for(int i = 1; i <= n; qs.pb(p[i++])) {
		while(sz(qs) > 1 && det(qs[sz(qs) - 2], qs.back(), p[i]) <= 0) qs.pop_back();
	}
	for(int i = n - 1, t = sz(qs); i; qs.pb(p[i--])) {
		while(sz(qs) > t && det(qs[sz(qs) - 2], qs.back(), p[i]) <= 0) qs.pop_back();
	}
	qs.pop_back(); 
}
ll calc(int l, int r, P a, P b) {
	if(l > r) r += sz(qs) / 2;
	if(r - l + 1 <= 2) return -inf;
	++l, --r;
	while(l + 4 < r) {
		int mid = l + r >> 1, mmid = mid + 1;
		if(abs(det(a - qs[mid], b - qs[mid])) > abs(det(a - qs[mmid], b - qs[mmid]))) {
			r = mmid;
		} else {
			l = mid;
		}
	}
	ll ans = 0;
	rep(i, l, r + 1) ans = max(ans, abs(det(a - qs[i], b - qs[i])));
	return ans;
}
void solve() {
	convex();
	int m = sz(qs);
	qs.insert(qs.end(), all(qs));
	rep(i, 0, m) assert(qs[i] == qs[i + m]);
	rep(i, 0, m) rep(j, i + 1, m) {
		ll ans = calc(i, j, qs[i], qs[j]) + calc(j, i, qs[i], qs[j]);
		ma = max(ans, ma);
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int I = 1e9;
	while(cin >> n) {
		rep(i, 1, n + 1) cin >> p[i].x >> p[i].y;
		//rep(i, 1, n + 1) p[i].x = rand() % I, p[i].y = rand() % I;
		sort(p + 1, p + 1 + n);
		n = unique(p + 1, p + 1 + n) - p - 1;
		if(n <= 3) {
			cout << 0 << " " << 0 << endl;
			continue;
		}
		rep(i, 1, n + 1) p[i].ind = i;
		m = 0;
		rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
			l[++m] = p[i] - p[j];
			if(l[m].x < 0) l[m].x *= -1, l[m].y *= -1;
			else if(l[m].x == 0 && l[m].y < 0) l[m].y *= -1;
			l[m].u = i, l[m].v = j;
		}
		sort(l + 1, l + 1 + m, cmp);
		rep(i, 1, n + 1) pos[p[i].ind] = i;
		mi = 4e18, ma = 0;
		rep(i, 1, m + 1) {
			int u = l[i].u, v = l[i].v;
			int pu = pos[u], pv = pos[v];
			if(pu > pv) swap(u, v), swap(pu, pv);
			if(pu == 1 || pv == n) continue;
			mi = min(mi, abs(det(p[pu] - p[pu - 1], p[pv] - p[pu - 1])) + abs(det(p[pu] - p[pv + 1], p[pv] - p[pv + 1])));
			swap(p[pu], p[pv]);
			swap(pos[u], pos[v]);
		}
		solve();
		cout << mi << " " << ma << endl;
	}
	return 0;
}
