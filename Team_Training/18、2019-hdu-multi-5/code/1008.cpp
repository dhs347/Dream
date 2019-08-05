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
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 1010;

struct P {
	int x, y; 
	P() {}
	P(int x, int y) : x(x), y(y) {}
	void read() {
		cin >> x >> y;
		x *= 2, y *= 2;
	}
	P operator + (const P &c) const {
		return P(x + c.x, y + c.y);
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	// zheng chu 
	P operator / (const int &c) const {
		return P(x / c, y / c);
	}
	bool operator == (const P &c) const {
		return x == c.x && y == c.y;
	}
};

int n;
P p[N];

ll det(P a, P b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
ll dot(P a, P b) {
	return 1ll * a.x * b.x + 1ll * a.y * b.y;
}

bool oo;
bool check(P s, P t, P i, P j) {
	P o = (s + t) / 2;
	P k = (i + j) / 2;
	if(det(s - t, i - j)) {
		if(!(i == j) && dot(s - t, i - o) == 0 && dot(s - t, j - o) == 0) oo = 0; 
		return 1;
	}
	if(dot(o - k, s - t)) return 1;
	return 0;
}
bool solve(int s, int t) {
	oo = 1;
	int m = (t - s) / 2;
	//dd(s), de(t);
	int cnt = 0;
	rep(d, 1, m + 1) {
		int i = s + d, j = t - d;
		if(i >= n) i -= n;
		if(j < 0) j += n;
		//dd(i), de(j);
		cnt += check(p[s], p[t], p[i], p[j]);
		if(cnt == 2) return 0;
	}
	m = (s + n - t) / 2;
	rep(d, 1, m + 1) {
		int i = s - d, j = t + d;
		if(i < 0) i += n;
		if(j >= n) j -= n;
		//dd(i), de(j);
		cnt += check(p[s], p[t], p[i], p[j]);
		if(cnt == 2) return 0;
	}
	return oo;
}

bool solve() {
	cin >> n;
	rep(i, 0, n) p[i].read();
	if(n < 5) return 1;
	rep(i, 0, 5) rep(j, i + 1, n) if(solve(i, j)) {
		dd(i), de(j);
		return 1;
	}
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << (solve() ? "Y" : "N") << endl;
	return 0;
}
