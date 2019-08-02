#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define dd(x) cout << #x << " = " << x << " "
#define de(x) cout << #x << " = " << x << endl
#define pw(x) (1ll<<(x))
#define endl "\n"
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 202020;

int xx, yy, ax, ay, bx, by, px, py, ne[20][N], ma[20][N], mi[20][N], x[N];
bool vis[N], inc[N];
ll n;

struct P {
	int x, y;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
};
ll det(P a, P b) {
	return a.x * 1ll * b.y - a.y * 1ll * b.x;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
ll area(vector<P> ps) {
	int n = sz(ps);
	ll ans = 0;
	rep(i, 0, n) ans += det(ps[i], ps[(i + 1) % n]);
	return abs(ans);
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
vector<P> ps;

void Ma(int &a, int b) {
	if(a < b) a = b;
}
void Mi(int &a, int b) {
	if(a > b) a = b;
}
map<int, int> mma, mmi;
void print() {
	int x = xx, y = yy;
	rep(i, 0, n) {
		Ma(mma[x], y);
		if(!mmi.count(x)) mmi[x] = y; else Mi(mmi[x], y);
		x = (x * 1ll * ax + bx) % px;
		y = (y * 1ll * ay + by) % py;
	}
}
int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> xx >> yy >> ax >> ay >> bx >> by >> px >> py >> n;
	int y = yy;
	vis[yy] = 1;
	int L = 1;
	print();
	rep(i, 1, n) {
		++L;
		int ny = (ay * 1ll * yy + by) % py;
		ne[0][yy] = ma[0][yy] = mi[0][yy] = ny;
		if(vis[ny]) break;
		vis[ny] = i + 1;
		yy = ny;
	}
	rep(i, 1, 20) rep(u, 0, py) {
		ne[i][u] = ne[i - 1][ne[i - 1][u]];
		Ma(ma[i][u], ma[i - 1][u]);
		Ma(ma[i][u], ma[i - 1][ne[i - 1][u]]);
		Mi(mi[i][u], mi[i - 1][u]);
		Mi(mi[i][u], mi[i - 1][ne[i - 1][u]]);
	}
	memset(vis, 0, sizeof(vis));
	x[0] = xx;
	vis[xx] = 1;
	int p;
	rep(i, 1, n) {
		x[i] = (ax * 1ll * x[i - 1] + bx) % px;
		if(vis[x[i]]) {
			rep(j, vis[x[i]], i + 1) inc[x[j]] = 1;
			p = i;
			break;
		}
		vis[x[i]] = i + 1;
	}
	rep(i, 0, p) {
		if(inc[x[i]]) {
			int yma = y, ymi = y, c = min(n - 1 - i, (ll)L), now = y;
			rep(j, 0, 20) if(c >> j & 1) {
				Ma(yma, ma[j][now]);
				Mi(ymi, mi[j][now]);
				now = ne[j][now];
			}
			ps.pb(P(x[i], yma));
			ps.pb(P(x[i], ymi));
			if(yma != mma[x[i]]) dd(x[i]), dd(yma), de(mma[x[i]]);
		//	if(ymi != mmi[x[i]]) dd(x[i]), dd(ymi), de(mmi[x[i]]);
		} else {
			ps.pb(P(x[i], y));
		}
		y = (y * 1ll * ay + by) % py;
	}
	ps = ch(ps);
	cout << area(ps) << endl;
	return 0;
}
