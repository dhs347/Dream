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
typedef long double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 66;

struct P {
	int i;
	int x, y;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	void read() {
		cin >> x >> y;
	}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	int len2() {
		return x * x + y * y;
	}
	db len() {
		return sqrt(len2());
	}
};

int n, k, cntp, cntt;
P a[N], ps[N], tmp[N];
int ans[N], cnta;
db res;

int det(P a, P b) {
	return a.x * b.y - a.y * b.x;
}
int det(P o, P a, P b) {
	return det(a - o, b - o);
}
int sign(ll x) {
	if(x > 0) x = 1;
	if(x < 0) x = -1;
	return x;
}

vector<P> ch(vector<P> &ps) {
	int n = sz(ps);
	if(n <= 1) return ps;
	sort(all(ps));
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
bool in(P p, const vector<P> &ps) {
	rep(i, 0, sz(ps)) {
		int j = (i == sz(ps) - 1 ? 0 : i + 1);
		if(det(ps[i], ps[j], p) < 0) return 0;
	}
	return 1;
}

void gao() {
	if(cntp <= k + 2) {
		int sel[N] = {0};
		rep(i, cntp - k + 1, cntp + 1) sel[i] = 1;
		do {
			vector<P> pt = vector<P>(k);
			int pos = 0;
			rep(i, 1, cntp + 1) if(sel[i]) pt[pos++] = ps[i];
			vector<P> p = ch(pt);
			db r = 0;
			rep(i, 0, sz(p)) {
				int j = (i == sz(p) - 1 ? 0 : i + 1);
				r += (p[i] - p[j]).len();
			}
			if(res > r) {
				res = r;
				cnta = k;
				rep(i, 0, cnta) ans[i] = pt[i].i;
			}
		} while(next_permutation(sel + 1, sel + 1 + cntp));
	} else {
		int old = cntp;
		db mi = 1e18; 
		rep(times, 0, 6) {
			random_shuffle(ps + 1, ps + 1 + cntp);
			vector<P> p = vector<P>(ps + 1, ps + 1 + k); p = ch(p);
			db r = 0;
			rep(i, 0, sz(p)) {
				int j = (i == sz(p) - 1 ? 0 : i + 1);
				r += (p[i] - p[j]).len();
			}
			if(res > r) {
				res = r;
				cnta = k;
				rep(i, 0, cnta) ans[i] = ps[i + 1].i;
			}
			if(mi > r) {
				mi = r;
				cntt = 0;
				rep(i, 1, cntp + 1) if(in(ps[i], p)) tmp[++cntt] = ps[i];
			}
		}
		if(cntt != old && cntt >= k) {
			cntp = cntt;
			rep(i, 1, cntt + 1) ps[i] = tmp[i];
			gao();
		}
	}
}

int main() {
	freopen("convexset.in", "r", stdin);
	freopen("convexset.out", "w", stdout);
	srand(time(0));
	/*
		 P x = P(0, 0);
		 vector<P> ps;
		 ps.pb(P(1, 1));
		 ps.pb(P(1, -1));
		 ps.pb(P(-1, 1));
		 ps.pb(P(-1, -1));
		 ps = ch(ps);
		 de(in(x, ps));
	 */
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	clock_t st = clock();
	cout << setiosflags(ios::fixed);
	cout << setprecision(7);
	cin >> n >> k;
	assert(n >= k);
	rep(i, 1, n + 1) a[i].read(), a[i].i = i;
	if(k == 1) {
		cout << 0. << endl;
		cout << 1 << endl;
	} else if(k == 2) {
		cout << 0. << endl;
		cout << 1 << " " << 2 << endl;
	} else {
		res = 1e18;
		sort(ps + 1, ps + 1 + n);
		rep(i, 1, n - k + 2 - 2) {
			int j = i + k - 1 + 2;
			cntp = k + 2;
			rep(t, 1, k + 1 + 2) ps[t] = a[i + t - 1];
			gao();
		}
		while((clock() - st) * 1. / CLOCKS_PER_SEC < 1.9) {
			int lx = rand() % 500, rx = lx + 500;
			int ly = rand() % 500, ry = ly + 500;
			if(lx > rx) swap(lx, rx);
			if(ly > ry) swap(ly, ry);
			cntp = 0;
			rep(i, 1, n + 1) if(lx <= ps[i].x && ps[i].x <= rx && ly <= ps[i].y && ps[i].y <= ry) ps[++cntp] = a[i];
			gao();
		}
		cout << res << endl;
		rep(i, 0, cnta) cout << ans[i] << " \n"[i == cnta - 1];
	}
	return 0;
}
