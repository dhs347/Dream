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

const int N = 404;

int n, g, r;

int sign(ll x) {
	if(x > 0) x = 1;
	if(x < 0) x = -1;
	return x;
}

struct P {
	int x, y;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	void read() {
		cin >> x >> y;
	}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	ll len2() {
		return 1ll * x * x + 1ll * y * y;
	}
	db len() {
		return sqrt(len2());
	}
}o[N];
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};

ll det(P a, P b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}

vector<P> ps;
bool ok[N][N];
int f[N][N];

db disToL(const L &l, const P &p) {
	return fabs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}

vector<P> ch(vector<P> ps) {
	int n = sz(ps); if(n <= 1) return ps;
	sort(all(ps));
	vector<P> qs;
	for(int i = 0; i < n; qs.pb(ps[i++])) {
		while(sz(qs) > 1 && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
	}
	for(int i = n - 2, t = sz(qs); i >= 0; qs.pb(ps[i--])) {
		while(sz(qs) > t && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
	}
	qs.pop_back(); return qs;
}

bool check(const L &l) {
	rep(i, 1, g + 1) if(disToL(l, o[i]) <= r) return 0;
	return 1;
}

int solve() {
	cin >> n >> g >> r;
	ps.clear();
	rep(i, 1, n + 1) {
		P p; p.read(); ps.pb(p);
	}
	rep(i, 1, g + 1) o[i].read();
	ps = ch(ps);
	if(sz(ps) <= 3) return 0;
	rep(i, 0, sz(ps)) rep(j, i + 1, sz(ps)) {
		bool &o = ok[i][j] = 1;
		if(j - i <= 1 || i + sz(ps) - j <= 1) {
			o = 0;
		} else {
			o = check(L(ps[i], ps[j]));
		}
	}
	rep(i, 0, sz(ps)) {
		ok[i][i] = 0;
		rep(j, 0, i) ok[i][j] = ok[j][i];
	}
	rep(i, 0, sz(ps)) rep(j, 0, sz(ps)) f[i][j] = 0;
	rep(len, 3, sz(ps) + 1) {
		for(int i = 0, j = len - 1; j < sz(ps); ++i, ++j) {
			f[i][j] = f[i + 1][j];
			rep(k, i + 1, j + 1) if(ok[i][k]) f[i][j] = max(f[i][j], max(f[i][k - 1], f[i + 1][k]) + f[k][j] + 1);
		}
	}
	return f[0][sz(ps) - 1];
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << solve() << endl;
	return 0;
}
