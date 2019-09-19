#include<algorithm>
#include<iostream>
#include<vector>
#include<deque>
#include<cmath>
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
typedef long double db;

const int N = 222;


const db eps = 1e-10;

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
	db len2() { return x * x + y * y; }
	db len() { return sqrt(len2()); }
	P norm() { return *this / len(); }
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
db dot(P a, P b) { return a.x * b.x + a.y * b.y; }
db det(P o, P a, P b) { return det(a - o, b - o); }
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
bool sameDir(L l0, L l1) {
	P a = l0.a - l0.b, b = l1.a - l1.b;
	return sign(det(a, b)) == 0 && sign(dot(a, b)) == 1;
}
bool operator < (const P &a,  const P &b) {
	if(a.quad() != b.quad()) {
		return a.quad() < b.quad();
	} else {
		return sign(det(a, b)) > 0;
	}
}
bool operator < (const L &l0, const L &l1) {
	if(sameDir(l0, l1)) {
		return l1.includer(l0.a);
	} else {
		return (l0.b - l0.a) < (l1.b - l1.a);
	}
}
P isLL(L l1, L l2) {
	db s1 = det(l2.b - l2.a, l1.a - l2.a);
	db s2 = -det(l2.b - l2.a, l1.b - l2.a);
	return (l1.a * s2 + l1.b * s1) / (s1 + s2);
}
bool check(L u, L v, L w) { return w.includer(isLL(u, v)); }
deque<L> halfPlane(vector<L> l) {
	sort(all(l));
	deque<L> q;
	rep(i, 0, sz(l)) {
		if(i && sameDir(l[i], l[i - 1])) continue;
		while(sz(q) > 1 && !check(q[sz(q) - 2], q.back(), l[i])) q.pop_back();
		while(sz(q) > 1 && !check(q[1], q[0], l[i])) q.pop_front();
		q.pb(l[i]);
	}
	while(sz(q) > 2 && !check(q[sz(q) - 2], q.back(), q[0])) q.pop_back();
	while(sz(q) > 2 && !check(q[1], q[0], q.back())) q.pop_front();
	return q;
}

int n, a[N][3];

/*
L ABC(db a,db b,db c){//Ax+By+C>0 line(s,t).pos(p)=1
	if(sign(c)&&sign(a)&&sign(b))return L(P(0.,-c/b),P(-c/a,0.));
	if(sign(c)&&sign(a)&&!sign(b))return L(P(-c/a,0.),P(-c/a,1.));
	if(sign(c)&&!sign(a)&&sign(b))return L(P(0.,-c/b),P(1.,-c/b));
	if(!sign(c)&&sign(a)&&sign(b))return L(P(0.,0.),P(-b,a));
	if(!sign(c)&&sign(a)&&!sign(b))return L(P(0.,0.),P(0.,1.));
	if(!sign(c)&&!sign(a)&&sign(b))return L(P(0.,0.),P(1.,0.));
}*/

bool solve(int i) { 
	if(n == 1) return 1;
	vector<L> ls;
	rep(j, 1, n + 1) if(i != j) {
		if(a[i][0] == a[j][0] && a[i][1] == a[j][1]) {
			if(a[i][2] <= a[j][2]) return 0;
			continue;
		}
		db t[3]; rep(o, 0, 3) t[o] = 1. * (a[i][o] - a[j][o]) / (a[i][o] * a[j][o]);
		ls.pb(L(t[0], t[1], t[2]));
	}
	db inf = 1e10;
	P o(0, 0), a(inf, 0), b(0, inf), c(inf, inf);
	ls.pb(L(o, a));
	ls.pb(L(b, o));
	ls.pb(L(a, c));
	ls.pb(L(c, b));
	return sz(halfPlane(ls)) > 2;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) rep(o, 0, 3) cin >> a[i][o];
	rep(i, 1, n + 1) cout << (solve(i) ? "Yes" : "No") << endl;
	return 0;
}
