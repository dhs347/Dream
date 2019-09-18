#include<vector>
#include<iostream>
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
typedef double db;

const int N = 50505;

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
};

int n;
P p[N];

ll det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
ll area(P a, P b, P c) {
	return abs(det(a, b, c));
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

// O(n ^ 2)
void maxAreaTri(P *p, int n, P &a, P &b, P &c) {
	int i = 0, j = 1, k = 2;
	a = p[i], b = p[j], c = p[k];
	ll res = area(a, b, c), cur = res, tmp;
	do {
		while(1) {
			while(cur <= (tmp = area(p[i], p[j], p[(k + 1) % n]))) (++k) %= n, cur = tmp;
			if(cur <= (tmp = area(p[i], p[(j + 1) % n], p[k]))) (++j) %= n, cur = tmp;
			else break;
		}
		if(cur > res) a = p[i], b = p[j], c = p[k], res = cur;
		(++i) %= n;
		if(i == j) (++j) %= n;
		if(j == k) (++k) %= n;
		cur = area(p[i], p[j], p[k]);
	} while(i);
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	while(cin >> n) {
		if(n == -1) break;
		rep(i, 0, n) p[i].read();
		vector<P> ps = ch(vector<P>(p, p + n));
		n = sz(ps); rep(i, 0, n) p[i] = ps[i];
		P a, b, c;
		maxAreaTri(p, n, a, b, c);
		ll ans = area(a, b, c);
		if(ans & 1) {
			cout << ans / 2 << ".50" << endl;
		} else {
			cout << ans / 2 << ".00" << endl;
		}
	}
	return 0;
}
