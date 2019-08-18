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
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef long double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 333;

struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	void read() {
		cin >> x >> y;
	}
	P rot() {
		return P(-y, x);
	}
	P operator + (const P &c) const {
		return P(x + c.x, y + c.y);
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	P operator * (const db &c) const {
		return P(x * c, y * c);
	}
	P operator / (const db &c) const {
		return P(x / c, y / c);
	}
	db len2() {
		return x * x + y * y;
	}
	db len() {
		return sqrtl(len2());
	}
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};

int n, m;
P p[N];
db ans, c[N];

db det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}

db disToL(L l, P p) {
	return det(p - l.a, l.b - l.a) / (l.b - l.a).len();
}

void solve(P a, P b) {
	L l(a, b);
	rep(i, 1, n + 1) c[i] = disToL(l, p[i]);
	nth_element(c + 1, c + m, c + n + 1);
	nth_element(c + m + 1, c + m + 1, c + n + 1);
	ans = max(ans, c[m + 1] - c[m]);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n; m = n >> 1;
	rep(i, 1, n + 1) p[i].read();
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
		solve(p[i], p[j]);
		P x = (p[i] + p[j]) / 2, y = (p[j] - x).rot() + x;
		solve(x, y);
	}
	cout << setiosflags(ios::fixed);
	cout << setprecision(12);
	cout << ans / 2 << endl;
	return 0;
}
