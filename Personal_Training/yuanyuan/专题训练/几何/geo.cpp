#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<cstdlib>
#include<iomanip>
#include<assert.h>
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

const int N = 505;
const db eps = 1e-8, pi = acos(-1.);

int sign(db x) { return (x > eps) - (x < -eps); }
struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	void read() { cin >> x >> y; }
	void print() { cout << x << " " << y << endl; }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	P operator * (const db &c) const { return P(x * c, y * c); }
	P operator / (const db &c) const { return P(x / c, y / c); }
	int quad() const { return sign(y) > 0 || (sign(y) == 0 && sign(x) >= 0); }
	P rot90() { return P(-y, x); }
	P rot(db a) { return P(cos(a) * x - sin(a) * y, cos(a) * y + sin(a) * x); }
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	P norm() { return *this / len(); }
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P o, P a, P b) { return det(a - o, b - o); }
db dot(P o, P a, P b) { return dot(a - o, b - o); }
struct O {
	P o; db r;
	O() {}
	O(P o, db r) : o(o), r(r) {}
	void read() {
		o.read(); cin >> r;
	}
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
	L(db a, db b, db c) {
		if(sign(a)==0) {
			this->a=P(0,-c/b);this->b=P(sign(b),-c/b);
		} else if(sign(b)==0) {
			this->a=P(-c/a,0);this->b=P(-c/a,-sign(a));
		} else {
			if(sign(c)!=0) {
				int x=sign(c)*sign(det(P(-c/a,0), P(0,-c/b)));
				if(x==1) this->a=P(-c/a,0),this->b=P(0,-c/b);
				else this->a=P(0,-c/b),this->b=P(-c/a,0);
			} else {
				//	y>=-a/b*x	b>0	(0,0)->(1,-a/b)
				//	y<=-a/b*x	b<0	(0,0)->(-1,a/b)
				this->a=P(0,0);this->b=P(sign(b),sign(b)*(-a/b));
			}
		}
	}
	bool includer(const P &p) const { return sign(det(b - a, p - a)) > 0; }
	// 向内（右手方向）推
	L push(db len) {
		P det = (b - a).rot90().norm() * len;
		return L(a + det, b + det);
	}
};
bool tanCP(O &c, P &p0, P &p1, P &p2) {
	db x = (p0 - c.o).len2(), d = x - c.r * c.r;
	if(d < eps) return 0;
	P p = (p0 - c.o) * (c.r * c.r / x);
	P det = ((p0 - c.o) * (-c.r * sqrt(d) / x)).rot90();
	p1 = c.o + p + det;
	p2 = c.o + p - det;
	return 1;
}
db disToL(L l, P p) {
	return fabs(det(l.a, p, l.b) / (l.b - l.a).len());
}
db disToS(L l, P p) {
	return sign(dot(l.a, p, l.b)) * sign(dot(l.b, p, l.a)) == 1 ? disToL(l, p) : min((p - l.a).len(), (p - l.b).len());
}
P isLL(L l1, L l2) {
	db s1 = det(l2.b - l2.a, l1.a - l2.a);
	db s2 = -det(l2.b - l2.a, l1.b - l2.a);
	return (l1.a * s2 + l1.b * s1) / (s1 + s2);
}
// sqrt((a ^ 2 + b ^ 2 + c ^ 2 + 4 * sqrt(3) * area) / 2)
// 如果有重点，大于 2 的直接用模拟退火法
P fermat(vector<P> p) {
	int n = sz(p); assert(n);
	if(n == 1) return p[0];
	if(n == 2) return (p[0] + p[1]) / 2;
	if(n == 3) {
		db a[3];
		rep(i, 0, 3) a[i] = (p[(i + 2) % 3] - p[(i + 1) % 3]).len();
		rep(i, 0, 3) {
			int j = (i + 1) % 3, k = (i + 2) % 3;
			if(sign(a[i] * a[i] - a[j] * a[j] - a[k] * a[k] - a[j] * a[k]) >= 0) return p[i];
		}
		if(det(p[0], p[1], p[2]) < 0) swap(p[1], p[2]);
		P q1 = (p[2] - p[0]).rot(pi / 3) + p[0]; 
		P q2 = (p[0] - p[1]).rot(pi / 3) + p[1];
		return isLL(L(q1, p[1]), L(q2, p[2]));
	}
	P ans(0, 0); rep(i, 0, n) ans = ans + p[i]; ans = ans / n;
	db len = 0; rep(i, 0, n) len += (ans - p[i]).len();
	db t = 100; // modify
	while(t > eps) {
		bool f = 1;
		while(f) {
			f = 0;
			for(int i = -1; i <= 1; i += 2) {
				for(int j = -1; j <= 1; j += 2) {
					P np(ans.x + i * t, ans.y + j * t);
					db k = 0; rep(i, 0, n) k += (np - p[i]).len();
					if(sign(len - k) > 0) ans = np, len = k, f = 1;
				}
			}
		}
		t *= 0.5;
	}
	return ans;
}

void solve() {
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(4);
	solve();
	return 0;
}
