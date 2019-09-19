#include<vector>
#include<iostream>
#include<deque>
#include<iomanip>
#include<cmath>
#include<algorithm>
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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double db;

const db eps = 1e-8;

int sign(db x) { return (x > eps) - (x < -eps); }
struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	void read() { cin >> x >> y; }
	void print() { cout << x << " " << y << endl; }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	P operator * (const db &c) const { return P(x * c, y * c); }
	P operator / (const db &c) const { return P(x / c, y / c); }
	int quad() const { return sign(y) > 0 || (sign(y) == 0 && sign(x) >= 0); }
	P rot90() { return P(-y, x); }
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	P norm() { return *this / len(); }
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P o, P a, P b) { return det(a - o, b - o); }
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
	bool includer(const P &p) const { return sign(det(b - a, p - a)) > 0; }
	bool include(const P &p) const { return sign(det(b - a, p - a)) >= 0; }
	// 向内（右手方向）推
	L push(db len) {
		P det = (b - a).rot90().norm() * len;
		return L(a + det, b + det);
	}
};
bool sameDir(L l0, L l1) {
	P a = l0.a - l0.b, b = l1.a - l1.b;
	return sign(det(a, b)) == 0 && sign(dot(a, b)) == 1;
}
bool operator < (const P &a,  const P &b) {
	if(a.quad() != b.quad()) {
		return a.quad() < b.quad();
	} else {
		return sign(det(a, b)) > 0;
	}
}
bool operator < (const L &l0, const L &l1) {
	if(sameDir(l0, l1)) {
		return l1.includer(l0.a);
	} else {
		return (l0.b - l0.a) < (l1.b - l1.a);
	}
}
P isLL(L l1, L l2) {
	db s1 = det(l2.b - l2.a, l1.a - l2.a);
	db s2 = -det(l2.b - l2.a, l1.b - l2.a);
	return (l1.a * s2 + l1.b * s1) / (s1 + s2);
}
bool check(L u, L v, L w) { return w.include(isLL(u, v)); }
deque<L> halfPlane(vector<L> l) {
	sort(all(l));
	deque<L> q;
	rep(i, 0, sz(l)) {
		if(i && sameDir(l[i], l[i - 1])) continue;
		while(sz(q) > 1 && !check(q[sz(q) - 2], q.back(), l[i])) q.pop_back();
		while(sz(q) > 1 && !check(q[1], q[0], l[i])) q.pop_front();
		q.pb(l[i]);
	}
	while(sz(q) > 2 && !check(q[sz(q) - 2], q.back(), q[0])) q.pop_back();
	while(sz(q) > 2 && !check(q[1], q[0], q.back())) q.pop_front();
	return q;
}

const int N = 1500;

int n;
P p[N];

bool check(db mid) {
	vector<L> l = vector<L>(n);
	rep(i, 0, n) l[i] = L(p[i], p[(i + 1) % n]).push(mid);
	return sz(halfPlane(l)) > 2;
}

void solve() {
	rep(i, 0, n) p[i].read();
	db sum = 0; rep(i, 1, n - 1) sum += det(p[0], p[i], p[i + 1]);
	if(sum < 0) reverse(p, p + n);

	db l = 0, r = 5050, ans;
	rep(i, 0, 100) {
		db mid = (l + r) / 2;
		if(check(mid)) {
			l = ans = mid;
		} else {
			r = mid; 
		}
	}
	cout << setiosflags(ios::fixed);
	cout << setprecision(6);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	while(cin >> n) {
		if(!n) break;
		solve();
	}
	return 0;
}
