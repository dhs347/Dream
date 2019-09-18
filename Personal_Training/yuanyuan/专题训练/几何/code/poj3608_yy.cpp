#include<vector>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<iosfwd>
#include<iomanip>
#include<iostream>
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
typedef double ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 10101;
const db eps = 1e-8;

int sign(db x) {
	return (x > eps) - (x < -eps);
}

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
	db len() {
		return sqrt(len2());
	}
	void print() {
		cout << x << " " << y << endl;
	}
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};

int n, m;
P p[N], q[N];
db ans;

ll det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
db dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}
db disToLine(L l, P p) {
	return fabs(det(p - l.a, l.b - l.a) / (l.b - l.a).len());
}
db disToSeg(L l, P p) {
	return sign(dot(p - l.a, l.b - l.a)) * sign(dot(p - l.b, l.a - l.b)) == 1 ? disToLine(l, p) : min((p - l.a).len(), (p - l.b).len());
}
bool isSS(L a,L b){ 
	db c1 = det(a.b - a.a, b.a - a.a), c2 = det(a.b - a.a, b.b - a.a),
		 c3 = det(b.b - b.a, a.a - b.a), c4 = det(b.b - b.a, a.b - b.a);
	return sign(c1) * sign(c2) <= 0 && sign(c3) * sign(c4) <= 0 &&
		sign(max(a.a.x, a.b.x) - min(b.a.x, b.b.x)) >= 0 &&
		sign(max(b.a.x, b.b.x) - min(a.a.x, a.b.x)) >= 0 &&
		sign(max(a.a.y, a.b.y) - min(b.a.y, b.b.y)) >= 0 &&
		sign(max(b.a.y, b.b.y) - min(a.a.y, a.b.y)) >= 0;
}
db disSS(L a, L b){ 
	if(isSS(a, b)) return 0;
	return min(min(disToSeg(b, a.a), disToSeg(b, a.b)), min(disToSeg(a, b.a), disToSeg(a, b.b)));
}

void gao(P p[], int n) {
	rep(i, 0, n) {
		int t = sign(det(p[i], p[(i - 1 + n) % n], p[(i + 1) % n]));
		if(t) {
			if(t < 0) reverse(p, p + n);
			return ;
		}
	}
}

void solve(P p[], int n, P q[], int m) {
	int o = 0, t = 0;
	rep(i, 1, n) if(p[i].y > p[o].y) o = i;
	rep(i, 1, m) if(q[i].y < q[t].y) t = i;
	rep(i, 0, n) {
		P a = p[(o + 1) % n] - p[o];
		db tmp;
		while((tmp = det(a, q[(t + 1) % m] - q[t])) < 0) t = (t + 1) % m;
		if(sign(tmp)) ans = min(ans, disToSeg(L(p[o], p[(o + 1) % n]), q[t]));
		else ans = min(ans, disSS(L(p[o], p[(o + 1) % n]), L(q[t], q[(t + 1) % m])));
		o = (o + 1) % n;
	}
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	while(cin >> n >> m) {
		if(!n && !m) break;
		rep(i, 0, n) p[i].read();
		rep(i, 0, m) q[i].read();
		gao(p, n);
		gao(q, m);
		ans = 1e18;
		solve(p, n, q, m);
		solve(q, m, p, n);
		cout << setiosflags(ios::fixed);
		cout << setprecision(5);
		cout << ans << endl;
	}
	return 0;
}

