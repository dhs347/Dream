#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); i++)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " " 
#define endl '\n'
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 1010;
const db eps = 1e-6;

struct P {
	int x, y;
	void read() {
		cin >> x >> y;
	}
	P() {}
	P(int x, int y) : x(x), y(y) {}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	ll len2() {
		return 1ll * x * x + 1ll * y * y;
	}
	void print() {
		dd(x), de(y);
	}
	db len() {
		return sqrt(len2());
	}
};
struct Line {
	int i, j; P ret;
	Line() {}
	Line(int i, int j, P ret) : i(i), j(j), ret(ret) {}
};

int n, cur[N], I, in[N][N], cntl, id[N];
P p[N];
Line line[N * N];

ll det(P a, P b) {
	return 1ll * a.x * b.y - 1ll * a.y * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
ll dot(P a, P b) {
	return 1ll * a.x * b.x + 1ll * a.y * b.y;
}
ll dot(P o, P a, P b) {
	return dot(a - o, b - o);
}

bool cmp(int i, int j) {
	P a = p[i] - p[I], b = p[j] - p[I];
	int o = P(0, 0) < a, t = P(0, 0) < b;
	if(o != t) return o < t;
	ll k = det(a, b);
	if(k) return k > 0;
	return a.len2() < b.len2();
}
db disToLine(Line &l) {
	P a = p[l.i], b = p[l.j];
	return det(a, a - b) / (b - a).len();
}
bool cmp2(Line i, Line j) {
	P a = i.ret, b = j.ret;
	int o = P(0, 0) < a, t = P(0, 0) < b;
	if(o != t) return o < t;
	ll k = det(a, b);
	if(k) return k > 0;
	return disToLine(i) < disToLine(j);
}
int calc(P a, P b, bool o = 0) {
	int l = 1, r = n, res = 0;
	while(l <= r) {
		int mid = l + r >> 1;
		ll t = det(a, b, p[cur[mid]]);
		bool flag = o ? (t <= 0) : (t < 0);
		if(flag) {
			res = mid;
			l = mid + 1;
		} else {
			r = mid - 1;
		}
	}
	return res;
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) p[i].read();
	sort(p + 1, p + 1 + n);
	rep(i, 1, n + 1) {
		I = i; rep(j, 1, n + 1) if(i != j) cur[j - (j > i)] = j;
		sort(cur + 1, cur + n, cmp);
		int cnt = 0;
		rep(k, 1, n) {
			int j = cur[k];
			ll et = det(p[i], p[j], p[cur[k - 1]]);
			ll ot = dot(p[i], p[j], p[cur[k - 1]]);
			if(k == 1 || et != 0 || (et == 0 && ot < 0)) cnt = 0;
			++cnt;
			in[i][j] = cnt - 1;
		}
	}
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) line[++cntl] = Line(i, j, p[j] - p[i]);
	rep(i, 1, n + 1) cur[i] = id[i] = i;
	sort(line + 1, line + 1 + cntl, cmp2);
	ll all = 0, res = 0;
	rep(_, 1, cntl + 1) {
		int i = line[_].i, j = line[_].j;
		int ii = id[i], ij = id[j];
		int x = calc(p[i], p[j]), y = n - calc(p[i], p[j], 1);
		all += x + y; 
		res += x * 1ll * (y + in[i][j]);
		res += y * 1ll * (x + in[i][j]);
		ll tt = det(line[_].ret, line[_ + 1].ret);
		if(_ < cntl && (tt || (tt == 0 && fabs(disToLine(line[_]) - disToLine(line[_ + 1])) > eps))) {
			int st = x + 1, ed = n - y;
			while(st < ed) {
				swap(cur[st], cur[ed]);
				swap(id[cur[st]], id[cur[ed]]);
				++st, --ed;
			}
		}
	}
	assert(all % 3 == 0);
	all /= 3; all *= (n - 3);
	ll ans = res - all;
	assert(ans % 2 == 0);
	cout << ans / 2 << endl;
	return 0;
}
