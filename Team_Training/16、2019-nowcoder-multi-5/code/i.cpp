#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a) --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long double db;

const db eps = 1e-7;

int b[3];

struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	P operator * (const db &c) const {
		return P(x * c, y * c);
	}
	P operator / (const db &c) const {
		return P(x / c, y / c);
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	void print() {
		cout << x << " " << y;
	}
	db len2() {
		return x * x + y * y;
	}
	db len() {
		return sqrt(len2());
	}
};

P ans[3];

bool check(int w, int h, int a, int b, int c) {
	P p = (a <= h ? P(0, a) : P(sqrt(a * a - h * h), h));
	P q = (c <= w ? P(c, 0) : P(w, sqrt(c * c - w * w)));
	if((p - q).len() < b) return 0;
	db co = (a * a + c * c - b * b) / 2. / a / c;
	db si = sqrt(1 - co * co);
	p = (q / q.len() * p.len());
	p = P(co * p.x - si * p.y, co * p.y + si * p.x);
	ans[0] = P(0, 0);
	ans[1] = p;
	ans[2] = q;
	return 1;
}

bool equ(P a, P b, int c) {
	db dis = (a - b).len();
	return dis - eps <= c && c <= dis + eps;
}

void solve() {
	int w, h, a[3];
	cin >> w >> h >> a[0] >> a[1] >> a[2];
	rep(i, 0, 3) b[i] = a[i];
	sort(a, a + 3);
	if(a[0] + a[1] == a[2]) {
		P p(w, h);
		db len = p.len();
		P t1 = p/len*a[1];
		P t2 = p/len*a[2];
		ans[0] = P(0, 0);
		ans[1] = t1;
		ans[2] = t2;
	} else {
		do {
			if(check(w, h, a[0], a[1], a[2])) break;
		} while(next_permutation(a, a + 3));
	}
	sort(ans, ans + 3);
	do {
		if(equ(ans[0], ans[1], b[0]) && equ(ans[0], ans[2], b[1]) && equ(ans[1], ans[2], b[2])) {
			rep(i, 0, 3) {
				ans[i].print();
				if(i != 2) cout << " ";
				else cout << endl;
			}
			break;
		}
	} while(next_permutation(ans, ans + 3));
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	cout << setiosflags(ios::fixed);
	cout << setprecision(8);
	while(T--) {
		solve();
	}
	return 0;
}
