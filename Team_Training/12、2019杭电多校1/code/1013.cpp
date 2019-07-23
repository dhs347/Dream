#include<bits/stdc++.h>
using namespace std;
#define fi first 
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define all(a) a.begin(), a.end()
#define sz(a) (int)a.size()
#define pw(x) (1ll << (x))
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 111;

int sign(ll x) {
	if(x > 0) x = 1;
	if(x < 0) x = -1;
	return x;
}

struct P {
	int x, y;
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
};

ll det(P a, P b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}

vector<P> ch(vector<P> ps) {
	int n = sz(ps);
	sort(all(ps));
	ps.erase(unique(all(ps)), ps.end());
	if(n <= 1) return ps;
	vector<P> qs;
	for(int i = 0; i < n; qs.pb(ps[i++])) {
		while(sz(qs) > 1 && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
	}
	for(int i = n - 2, t = sz(qs); i >= 0; qs.pb(ps[i--])) {
		while(sz(qs) > t && sign(det(qs[sz(qs) - 2], qs.back(), ps[i])) <= 0) qs.pop_back();
	}
	qs.pop_back();
	return qs;
}

bool check(vector<P> &ps, vector<P> &qs) {
	if(sz(ps) == 1) return 0;
	rep(i, 0, sz(ps)) {
		int j = (i + 1) % sz(ps);
		bool ok = 1;
		rep(k, 0, sz(qs)) if(sign(det(ps[i], ps[j], qs[k])) >= 0) {
			ok = 0;
			break;
		}
		if(ok) return 1;
	}
	return 0;
}

bool solve() {
	vector<P> ps[2];
	int n; cin >> n;
	rep(i, 1, n + 1) {
		int x, y, o;
		cin >> x >> y >> o;
		ps[o == 1].pb(P(x, y));
	}
	rep(o, 0, 2) ps[o] = ch(ps[o]);
	if(max(sz(ps[0]), sz(ps[1])) <= 1) {
		if(sz(ps[0]) == 1 && sz(ps[1]) == 1 && ps[0][0] == ps[1][0]) return 0;
		return 1;
	}
	if(check(ps[0], ps[1])) return 1;
	if(check(ps[1], ps[0])) return 1;
	return 0;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) cout << (solve() ? "Successful!" : "Infinite loop!") << endl;
	return 0;
}
