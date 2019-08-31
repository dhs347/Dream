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

const db pi = acos(-1);

struct P {
	int x, y;
	void read() {
		cin >> x >> y;
	}
	P() {}
	P(int x, int y) : x(x), y(y) {}
	P operator -(const P &c) const {
		return P(x - c.x, y - c.y);
	}
	ll len2() {
		return 1ll * x * x + 1ll * y * y;
	}
	db len() {
		return sqrt(len2());
	}
};

ll dot(P a, P b) {
	return 1ll * a.x * b.x + 1ll * a.y * b.y;
}

vector<P> ps;
P o;

void solve() {
	ps.clear();
	int n; cin >> n;
	rep(i, 0, n) {
		P p; p.read(); ps.pb(p);
	}
	o.read();
	db ans = 0;
	rep(i, 0, n) {
		int j = (i - 1 + n) % n;
		int k = (i + 1) % n;
		P p1 = ps[j] - ps[i], p2 = ps[k] - ps[i];
		db ret = pi - fabs(acos(dot(p1, p2) / p1.len() / p2.len()));
		ans += ret * (o - ps[i]).len();
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	cout << setiosflags(ios::fixed);
	cout << setprecision(3);
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}
