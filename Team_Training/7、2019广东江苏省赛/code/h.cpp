#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define endl "\n"
#define pw(x) (1ll << (x))
#define all(x) x.begin(), x.end()
#define sz(a) (int)a.size()
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
typedef long long ll;
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int N = 101010;

int n, q, k, dis[N], ne[N], go[N][2];
ll ans[N];
char s[N];
pair<pii, int> Q[N];
vi vec, g[N];
vector<pii> vv[N];
bool check() {
	rep(i, 1, sz(vec)) if(s[vec[i]] != s[vec[0]]) return 0;
	return 1;
}
void gao(int st) {
	vec.clear();
	vec.pb(st);
	for(int p = (st + k) % n; p != st; p = (p + k) % n) vec.pb(p);
	if(!check()) {
		vi que;
		for(auto p : vec) if(ne[ne[p]] == p) dis[p] = 0, go[p][0] = p, go[p][1] = ne[p], que.pb(p);
		rep(i, 0, sz(que)) {
			int u = que[i];
			for(auto v : g[u]) {
				if(dis[v] > dis[u] + 1) {
					dis[v] = dis[u] + 1;
					go[v][0] = go[u][1];
					go[v][1] = go[u][0];
					que.pb(v);
				}
			}
		}
	}
}
struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int cnt[2][N], cc[2];
	ll sum[4][N], ss[4];
	void build(int n) {
		++n;
		fill_n(cnt[0] + 1, n << 2, 0);
		fill_n(cnt[1] + 1, n << 2, 0);
		rep(i, 0, 4) fill_n(sum[i] + 1, n << 2, 0);
	}
	void up(int rt) {
		rep(o, 0, 2) cnt[o][rt] = cnt[o][ls] + cnt[o][rs];
		rep(o, 0, 4) sum[o][rt] = sum[o][ls] + sum[o][rs];
	}
	void upd(int p, int l, int r, int rt) {
		if(l == r) {
			++cnt[s[p] == '('][rt];
			sum[s[p] == '('][rt] += p;
			sum[2][rt] += go[p][0];
			sum[3][rt] += go[p][1];
			return ;
		}
		int mid = l + r >> 1;
		if(dis[p] <= mid) upd(p, l, mid, ls);
		else upd(p, mid + 1, r, rs);
		up(rt);
	}
	void qry(int L, int R, int l, int r, int rt) {
		if(rt == 1) {
			rep(o, 0, 2) cc[o] = 0;
			rep(o, 0, 4) ss[o] = 0;
		}
		if(L > R) return ;
		if(L <= l && r <= R) {
			rep(o, 0, 2) cc[o] += cnt[o][rt];
			rep(o, 0, 4) ss[o] += sum[o][rt];
			return ;
		}
		int mid = l + r >> 1;
		if(L <= mid) qry(L, R, l, mid, ls);
		if(R > mid) qry(L, R, mid + 1, r, rs);
	}
}seg;

void gao(int l, int r, int w, int i) {
	l = max(l, 0);
	r = min(r, n - 1);
	if(l > r) return ;
	if(l) vv[l - 1].pb(mp(w, -i));
	vv[r].pb(mp(w, i));
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	while(cin >> n >> q >> k >> s) {
		///init
		rep(i, 0, n) dis[i] = n;
		rep(i, 1, q + 1) ans[i] = 0;
		rep(i, 0, n) g[i].clear(), vv[i].clear();
		seg.build(n);
		///solve
		rep(i, 1, q + 1) {
			int l, r, d;
			cin >> l >> r >> d;
				Q[i] = mp(mp(l, r), d);
				int c = k * 1ll * d % n;
				int m1 = n - c, m2 = c;
				gao(l, min(r, m1 - 1), 1, i);
				gao(max(l, m1), r, 2, i);
				gao(l, min(r, m2 - 1), 3, i);
				gao(max(l, m2), r, 4, i);
				gao(l, r, 5 + (d & 1), i);
			}
		rep(u, 0, n) {
			int v = (s[u] == '(' ? (u - k + n) % n : (u + k) % n);
			g[v].pb(u);
			ne[u] = v;
		}
		int Gcd = __gcd(n, k);
		rep(i, 0, Gcd) gao(i);
		rep(i, 0, n) {
			seg.upd(i, 0, n, 1);
			for(auto u : vv[i]) {
				int ind = abs(u.se), w = u.se / ind;
				int d = Q[ind].se, c = k * 1ll * d % n;
				d = min(d, n);
				if(u.fi <= 4) seg.qry(d, n, 0, n, 1);
				else seg.qry(0, d - 1, 0, n, 1);
				ll res = 0;
				if(u.fi == 1) {
					res += seg.ss[0] + seg.cc[0] * 1ll * c;
				} else if(u.fi == 2) {
					res += seg.ss[0] + seg.cc[0] * 1ll * c - seg.cc[0] * 1ll * n;
				} else if(u.fi == 3) {
					res += seg.ss[1] - seg.cc[1] * 1ll * c + seg.cc[1] * 1ll * n;
				} else if(u.fi == 4) {
					res += seg.ss[1] - seg.cc[1] * 1ll * c;
				} else {
					res += seg.ss[u.fi - 3];
				}
				ans[ind] += res * w;
			}
		}
		rep(i, 1, q + 1) {
			cout << ans[i] << endl;
		}
	}
	return 0;
}
