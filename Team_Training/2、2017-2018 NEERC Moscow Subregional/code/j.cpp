#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define mp make_pair
#define pb push_back
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(a) (1ll << (a))
#define endl "\n"
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;
const db eps = 1e-8;

int n, w, h;
pii tri[N][3];
db A[N], B[N];

void solve(db x) {
	vector<pair<db, db> > seg;
	rep(i, 1, n + 1) {
		vector<db> vec;
		rep(j, 0, 3) {
			pii p = tri[i][j], q = tri[i][(j + 1) % 3];
			if(p.fi > q.fi) swap(p, q);
			if(p.fi < x && x < q.fi) vec.pb((q.se - p.se) * 1. * (x - p.fi) / (q.fi - p.fi) + p.se);
		}
		sort(all(vec));
		if(sz(vec)) seg.pb(mp(vec[0], vec[1]));
	}
	seg.pb(mp(0, 0));
	seg.pb(mp(h, h));
	sort(all(seg));
	db ans, ma = 0;
	rep(i, 1, sz(seg)) if(seg[i - 1].se < seg[i].fi) {
		db a = seg[i - 1].se, b = seg[i].fi;
		if(b - a > ma) {
			ma = b - a;
			ans = (a + b) / 2;
		}
	}
	cout << x << " " << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(9);
	cin >> n >> w >> h;
	rep(i, 1, n + 1) {
		rep(j, 0, 3) cin >> tri[i][j].fi >> tri[i][j].se;
		sort(tri[i], tri[i] + 3);
		int x[3], y[3];
		rep(j, 0, 3) x[j] = tri[i][j].fi, y[j] = tri[i][j].se;
		db yy = (y[2] - y[0]) * 1. * (x[1] - x[0]) / (x[2] - x[0]) + y[0];
		if(x[0] != x[1]) {
			db a = fabs(yy - y[1]) / (x[1] - x[0]);
			db b = -a * x[0];
			A[x[0]] += a, B[x[0]] += b;
			A[x[1]] -= a, B[x[1]] -= b;
		} 
		if(x[1] != x[2]) {
			db a = fabs(yy - y[1]) / (x[1] - x[2]);
			db b = -a * x[2];
			A[x[1]] += a, B[x[1]] += b;
			A[x[2]] -= a, B[x[2]] -= b;
		}
	}
	db x = 0, mi = h * 2, a = 0, b = 0;
	rep(i, 0, w) {
		a += A[i], b += B[i];
		if(mi > a * (i + eps) + b) {
			mi = a * (i + eps) + b;
			x = i + eps;
		}
		if(mi > a * (i + 1 - eps) + b) {
			mi = a * (i + 1 - eps) + b;
			x = i + 1 - eps;
		}
	}
	solve(x);
	return 0;
}
