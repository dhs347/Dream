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
#define endl '\n'
#define pw(x) (1ll<<(x))
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef pair<int, int> pii;
typedef long double db;
typedef vector<int> vi;

const db eps = 1e-10;

db a, b, c, d, e, f, d1, d2, ang, cc;

db sqr(db a) {return a * a;}

db angle() {
	db t1 = sqrt(sqr(a) + sqr(b));
	db t2 = sqrt(sqr(c) + sqr(d));
	db x = (a * c + b * d) / t1 / t2;
	//de(r);
	db r = acos(x);
	return fabs(r);
}
int sign(db x) {
	return (x > eps) - (x < -eps);
}
bool check() {
	db det = a * d - c * b;
	if(sign(det)) return 0;
	return sign(a) == sign(c) && sign(b) == sign(d);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(10);		
	cin >> a >> b >> c >> d >> e >> f;
	a -= e;
	c -= e;
	b -= f;
	d -= f;
	d1 = sqrt(a * a + b * b);
	d2 = sqrt(c * c + d * d);
	/*if (d1 < d2) {
		swap(d1, d2);
		swap(a, c);
		swap(b, d);
	}*/
	//dd(a),de(b); 
	//dd(c),de(d); 
	if(check()) {
		cout << fabs(d1 - d2) << endl;
		return 0;
	}

	db pi = acos(-1);
	ang = angle();
	//de(ang);
	if (fabs(d1 - d2) <= eps) {
		cout << ang * d1 << endl;
	}else {
		//de(233);
		cc = ang / log(d2 / d1);
		db ans1 = cc  * sqrt(d1 * d1 + d1 * d1 / cc / cc) * (exp(ang / cc) - 1);;
		ang = 2 * pi - ang;
		cc = ang / log(d2 / d1);
		db ans2 = cc * d1 * (d2 / d1 - 1);;
		//assert(min(ans1, ans2) >= 0);
		cout << ans1 << endl;
	}
	return 0;
}
