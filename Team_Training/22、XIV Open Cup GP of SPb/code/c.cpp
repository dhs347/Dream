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
typedef long double db;

const int N = 66, K = 22;

struct P {
	int x, y, i;
	P() {}
	P(int x, int y) : x(x), y(y) {}
	void read() { cin >> x >> y; }
	P operator - (const P &c) const {
		return P(x - c.x, y - c.y);
	}
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
	int len2() {
		return x * x + y * y;
	}
	db len() {
		return sqrt(len2());
	}
};
struct L {
	P a, b;
	L() {}
	L(P a, P b) : a(a), b(b) {}
};
ll det(P a, P b) {
	return a.x * 1ll * b.y - a.y * 1ll * b.x;
}
struct Node {
	int i, j; P p;
	Node() {}
	Node(int i, int j, P p) : i(i), j(j), p(p) {}
	bool operator < (const Node &c) const {
		int o = P(0, 0) < p, t = P(0, 0) < c.p;
		if(o != t) return o < t;
		return det(p, c.p) > 0;
	}
}nd[N * N];
int cntn;
ll dot(P a, P b) {
	return a.x * 1ll * b.x + a.y * 1ll * b.y;
}
ll det(P o, P a, P b) {
	return det(a - o, b - o);
}
int sign(ll x) {
	if(x > 0) x = 1;
	if(x < 0) x = -1;
	return x;
}

int n, k;
P p[N];
db f[N][K][N];
pii pre[N][K][N];
int c1[N][N], c2[N][N][N];

bool onSeg(L l, P p) {
	return det(p - l.a, l.b - l.a) == 0 && dot(p - l.a, p - l.b) <= 0;
}
bool in(P a, P b, P c, P p) {
	int oa = sign(det(p, a, b));
	int ob = sign(det(p, b, c));
	int oc = sign(det(p, c, a));
	return oa == ob && oa == oc;
}
void Mi(db &a, db b) {
	if(a > b) a = b;
}
int calc(int i, int j) {
	if(i == j) return 1;
	if(i > j) swap(i, j);
	return c1[i][j];
}
int calc(int i, int j, int k) {
	if(i > j) swap(i, j);
	if(i > k) swap(i, k);
	if(j > k) swap(j, k);
	if(i == j) return c1[i][k];
	if(j == k) return c1[i][j];
	return c2[i][j][k];
}
bool in(P p, vector<P> ps) {
	rep(i, 0, sz(ps)) {
		int j = (i == sz(ps) - 1 ? 0 : i + 1);
		if(det(ps[j], ps[i], p) < 0) return 0;
	}
	return 1;
}
int main() {
	freopen("convexset.in", "r", stdin);
	freopen("convexset.out", "w", stdout);
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cout << setiosflags(ios::fixed);
	cout << setprecision(7);
	cin >> n >> k;
	rep(i, 1, n + 1) p[i].read(), p[i].i = i;
	if(k == 1) {
		cout << 0. << endl << 1 << endl;
		return 0;
	} else if(k == 2) {
		cout << 0. << endl << "1 2" << endl;
		return 0;
	}
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
		rep(k, 1, n + 1) c1[i][j] += onSeg(L(p[i], p[j]), p[k]);
	//	dd(i), dd(j), de(c1[i][j]);
	}
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) rep(k, j + 1, n + 1) {
		rep(t, 1, n + 1) c2[i][j][k] += in(p[i], p[j], p[k], p[t]);
		c2[i][j][k] += 3;
//		dd(i), dd(j), dd(k), de(c2[i][j][k]);
	}
	rep(i, 1, n + 1) rep(j, 1, n + 1) if(i != j) {
		nd[++cntn] = Node(i, j, p[j] - p[i]); // ij
	}
	sort(nd + 1, nd + 1 + cntn);
	rep(i, 0, N) rep(j, 0, K) rep(k, 0, N) f[i][j][k] = 1e18;
	rep(i, 1, n + 1) f[i][1][i] = 0;
	rep(_, 1, cntn + 1) {
		int j = nd[_].i, t = nd[_].j;
	//	dd(_), dd(j), de(t);
		rep(s, 1, n + 1) if(s != t && (s == j || det(p[j], p[t], p[s]) > 0)) rep(i, 1, k + 1) {
			int ad = calc(s, j, t) - calc(s, j);
			//de(ad);
			if(i + ad <= k) {
				db &x = f[s][i + ad][t];
				db y = f[s][i][j] + (p[t] - p[j]).len();
				if(x > y) {
					x = y;
					pre[s][i + ad][t] = mp(i, j);
				}
				//dd(i + ad), dd(s), dd(t), de(f[s][i + ad][t]);
			}
		}
	}
	int I = 1, J = 2;
	db ans = 1e18;
	rep(i, 1, n + 1) rep(j, 1, n + 1) if(i != j) {
		db res = f[i][k][j] + (p[i] - p[j]).len();
		if(ans > res) {
			ans = res; I = i, J = j;
		}
	}
	cout << ans << endl;
//	de(I);
	vector<P> res;
	while(J) {
		res.pb(p[J]);
		auto t = pre[I][k][J];
	//	dd(I), dd(k), de(J);
		k = t.fi, J = t.se;
	}
	vi vec;
	rep(i, 1, n + 1) if(in(p[i], res)) vec.pb(i);
	rep(i, 0, sz(vec)) cout << vec[i] << " \n"[i == sz(vec) - 1];
	return 0;
}
