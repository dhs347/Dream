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

const int N = 1010;
const db eps = 1e-8;

int sign(db x) { return (x > eps) - (x < -eps); }
struct P {
	db x, y;
	P() {}
	P(db x, db y) : x(x), y(y) {}
	void read() { cin >> x >> y; }
	P operator + (const P &c) const { return P(x + c.x, y + c.y); }
	P operator - (const P &c) const { return P(x - c.x, y - c.y); }
	P operator * (const db &c) const { return P(x * c, y * c); }
	P operator / (const db &c) const { return P(x / c, y / c); }
	bool operator < (const P &c) const {
		if(x != c.x) return x < c.x;
		return y < c.y;
	}
};
db det(P a, P b) { return a.x * b.y - a.y * b.x; }
struct L {
	P a, b;
	vector<pair<P, int> > ps;
	L() {}
	L(P a, P b) : a(a), b(b) {}
	void read() { a.read(); b.read(); }
};

int n, cnte, V, ne[N * N * 2];
pii E[N * N * 2];
L l[N];
vector<P> ps;
bool vis[N * N * 2];
vector<pii> g[N * N];
vector<db> ans;

bool cmp(const pii &i, const pii &j) {
	P a = ps[i.fi] - ps[V], b = ps[j.fi] - ps[V];
	int o = P(0, 0) < a, t = P(0, 0) < b;
	if(o != t) return o < t;
	return det(a, b) > 0;
}
void go(int e) {
	db res = 0;
	while(!vis[e]) {
		res += det(ps[E[e].se], ps[E[e].fi]); vis[e] = 1;
		e = ne[e ^ 1];
	}
	if(res > 0) ans.pb(res / 2);
}
void go(int u, int v, int e) {
	db res = 0;
	while(!vis[e]) {
		res += det(ps[v], ps[u]); vis[e] = 1;
		rep(i, 0, sz(g[v])) if(g[v][i].fi == u) {
			int j = (i + 1) % sz(g[v]);
			u = g[v][j].fi; e = g[v][j].se;
			swap(u, v);
			break;
		}
	}
	if(res > 0) ans.pb(res / 2);
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) l[i].read();
	rep(i, 1, n + 1) rep(j, i + 1, n + 1) {
		db s1 =  det(l[j].b - l[j].a, l[i].a - l[j].a);
		db s2 = -det(l[j].b - l[j].a, l[i].b - l[j].a);
		if(sign(s1 + s2)) {
			P p = (l[i].a * s2 + l[i].b * s1) / (s1 + s2);
			l[i].ps.pb(mp(p, sz(ps))), l[j].ps.pb(mp(p, sz(ps)));
			ps.pb(p); 
		}
	}
	rep(i, 1, n + 1) {
		sort(all(l[i].ps));
		rep(j, 1, sz(l[i].ps)) {
			int u = l[i].ps[j - 1].se, v = l[i].ps[j].se;
			E[cnte] = mp(u, v);
			g[u].pb(mp(v, cnte++));
			E[cnte] = mp(v, u);
			g[v].pb(mp(u, cnte++));
		}
	}
	rep(i, 0, sz(ps)) {
		V = i;
		sort(all(g[i]), cmp);
		rep(j, 0, sz(g[i])) {
			ne[g[i][j].se] = g[i][(j + 1) % sz(g[i])].se;
		}
	}
	rep(i, 0, cnte) if(!vis[i]) go(i);
	//	rep(u, 0, sz(ps)) for(auto v : g[u]) if(!vis[v.se]) go(u, v.fi, v.se);

	sort(all(ans)); reverse(all(ans));
	cout << setiosflags(ios::fixed);
	cout << setprecision(5);
	cout << sz(ans) << " " << ans[0] << " " << ans.back() << endl;
	int q; cin >> q;
	while(q--) {
		int k; cin >> k;
		if(k > sz(ans)) cout << "Invalid question" << endl;
		else cout << ans[k - 1] << endl;
	}
	return 0;
}
