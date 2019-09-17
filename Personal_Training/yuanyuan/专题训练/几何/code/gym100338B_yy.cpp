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

db sum;

struct P {
	db x, y; 
	void read() {
		scanf("%lf%lf", &x, &y);
		sum += fabs(x) + fabs(y);
	}
	P() {}
	P(db x, db y) : x(x), y(y) { }
	P operator + (const P &c) {
		return P(x + c.x, y + c.y);
	}
	P operator - (const P &c) {
		return P(x - c.x, y - c.y);
	}
	P operator / (const db &c) {
		return P(x / c, y / c);
	}
	db len2() {
		return x * x + y * y;
	}
};

int main() {
	freopen("geometry.in", "r", stdin);
	freopen("geometry.out", "w", stdout);
	while(1) {
		sum = 0;
		P p[4]; rep(i, 0, 4) p[i].read();
		if(sum < 1) break;
		P a, b; db dis = 1e18;
		rep(i, 0, 2) rep(j, 2, 4) if((p[i] - p[j]).len2() < dis) {
			dis = (p[i] - p[j]).len2();
			a = p[i], b = p[j];
		}
		P ans = (a + b) / 2; db res = sqrt(dis) / 2 + 0.005;
		printf("%.5f %.5f %.5f\n", ans.x, ans.y, res);
	}
	return 0;
}
