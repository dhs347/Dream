#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define endl "\n"
#define pw(a) (1ll << (a))
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 111;
const db pi = acos(-1);

int n;
struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	void read() {
		scanf("%lf%lf", &x, &y);
	}
}p[N];

db dis(P a, P b) {
	db x = a.x - b.x;
	db y = a.y - b.y;
	return sqrt(x * x + y * y);
}
db dot(P a, P b) {
	return a.x * b.x + a.y * b.y;
}
db det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
db rad(P p1, P p2) {
	return atan2l(det(p1, p2), dot(p1, p2));
}

void solve() {
	cin >> n;
	rep(i, 0, n + 1) p[i].read();
	db ans = 0;
	rep(i, 0, n) {
		int j = (i - 1 + n) % n;
		int k = (i + 1) % n;
		db ii = dis(p[i], p[n]), jj = rad(p[j] - p[i], p[k] - p[i]);
		ans += ii * (pi - fabs(jj));
	}
	printf("%.3f\n", ans);
}

int main() {
	int T;
	cin >> T;
	int ca =  0;
	while(T--) {
		cout << "Case #" << ++ca << ": ";
		solve();
	}
	return 0;
}
