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
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define endl '\n'
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

struct P {
	ll x, y;
	P() {}
	P(ll x, ll y) : x(x), y(y) {}
	P operator + (const P &c) const {
		return P(x + c.x, y + c.y);
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	bool operator == (const P &c) const {
		return x == c.x && y == c.y;
	}
	void read() {
		cin >> x >> y;
	}
};
ll det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}

struct Node {
	ll x, y;
	Node() {}
	Node(ll _x, ll _y) {
		ll g = __gcd(_x, _y);
		x = _x / g;
		y = _y / g;
		if(y < 0) x = -x, y = -y;
	}
	ll get() {
		if(x >= 0) {
			return x / y;
		} else {
			ll t = -x;
			return -(t / y + 1);
		}
	}
};

void solve() {
	P a, c, p, o = P(0, 0);
	a.read();
	c.read();
	p.read();
	if(det(a, c) < 0) swap(a, c);
	P b = c + a;
	Node x = Node(det(a, p), det(a, c));
	Node y = Node(det(p, c), det(a, c));
	if(x.y == 1 || y.y == 1) {
		cout << -1 << endl;
		return ;
	}
	ll xv = x.get(), yv = y.get();
	cout << 4 * (abs(xv) + abs(yv)) << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
