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
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

struct P {
	ll x, y, z;
	void read() {
		cin >> x >> y >> z;
	}
	P() {}
	P(ll x, ll y, ll z) : x(x), y(y), z(z) {}
	P operator - (const P &c) {
		return P(x - c.x, y - c.y, z - c.z);
	}
	bool zero() {
		return !x && !y && !z;
	}
};

P det(P a, P b) {
	return P(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
ll dot(P a, P b) {
	return a.x * b.x + a.y * b.y + a.z * b.z;
}

int n;
P p[N], q;

bool solve() {
	if(n <= 3) return 1;
	rep(i, 3, n + 1) {
		q = det(p[2] - p[1], p[i] - p[1]);
		if(!q.zero()) break;
	}
	if(q.zero()) return 1;
	rep(i, 1, n + 1) if(dot(q, p[i] - p[1])) return 0;
	return 1;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) p[i].read();
	cout << (solve() ? "TAK" : "NIE") << endl;
	return 0;
}
