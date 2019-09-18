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

struct P {
	ll x, y;
	void read() {
		cin >> x >> y;
	}
	bool operator < (const P &c) {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	P() {}
	P(ll x, ll y) : x(x), y(y) {}
	P operator - (const P &c) {
		return P(x - c.x, y - c.y);
	}
	ll len2() {
		return x * x + y * y;
	}
	void print() {
		cout << x << " " << y << endl;
	}
};

ll det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
ll dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}

vector<P> ch(vector<P> ps) {
	int n = sz(ps); if(n <= 1) return ps;
	sort(all(ps));
	vector<P> qs;
	for(int i = 0; i < n; qs.pb(ps[i++])) {
		while(sz(qs) > 1 && det(qs[sz(qs) - 2], qs.back(), ps[i]) <= 0) qs.pop_back();
	}
	for(int i = n - 2, t = sz(qs); i >= 0; qs.pb(ps[i--])) {
		while(sz(qs) > t && det(qs[sz(qs) - 2], qs.back(), ps[i]) <= 0) qs.pop_back();
	}
	qs.pop_back();
	return qs;
}

void solve() {
	int n; cin >> n; n <<= 2;
	vector<P> ps = vector<P>(n);
	rep(i, 0, n) ps[i].read();
	ps = ch(ps); n = sz(ps);
	reverse(all(ps));
	db ans = 1e18;
	int p = 1, l = 1, r;
	rep(i, 0, n) {
		P t = ps[i] - ps[(i + 1) % n];
		while(det(t, ps[(p + 1) % n] - ps[p]) > 0) p = (p + 1) % n;	
		while(dot(t, ps[(l + 1) % n] - ps[l]) < 0) l = (l + 1) % n;
		r = (p + 1) % n;
		while(dot(t, ps[(r + 1) % n] - ps[r]) > 0) r = (r + 1) % n;
		ll et = abs(det(ps[p], ps[i], ps[(i + 1) % n]));
		ll ot = abs(dot(t, ps[l] - ps[r]));
		ans = min(ans, (db)et * ot / t.len2());
	}

	cout << setiosflags(ios::fixed);
	cout << setprecision(0);
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T; cin >> T;
	rep(ca, 1, T + 1) cout << "Case #" << ca << ":" << endl, solve();
	return 0;
}
