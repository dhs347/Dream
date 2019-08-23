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
typedef double db;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef long long ll;

const int N = 1e6 + 7;

int n, q, l, w;
ll ans[N];
vector<pair<int, pii> > vec[N];
int x[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	ll a[N], la[N];
	void gao(int rt, ll c, int l, int r) {
		a[rt] += c * (r - l + 1);
		la[rt] += c;
	}
	void down(int rt, int l, int r, int mid) {
		if(la[rt]) {
			gao(ls, la[rt], l, mid);
			gao(rs, la[rt], mid + 1, r);
			la[rt] = 0;
		}
	}
	void up(int rt) {
		a[rt] = a[ls] + a[rs];
	}
	void upd(int L, int R, ll c, int l = 0, int r = 1e6, int rt = 1) {
		if(L <= l && r <= R) {
			gao(rt, c, l, r);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	ll qry(int L, int R, int l = 0, int r = 1e6, int rt = 1) {
		if(L <= l && r <= R) return a[rt];
		int mid = l + r >> 1;
		ll ans = 0;
		down(rt, l, r, mid);
		if(L <= mid) ans += qry(L, R, l, mid, ls);
		if(R > mid) ans += qry(L, R, mid + 1, r, rs);
		return ans;
	}
}seg[3];
// cnt, xl, pre

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> q >> l >> w;
	rep(i, 1, n + 1) {
		int xl, yl, xr, yr;
		cin >> xl >> yl >> xr >> yr;
		// xl, xr - 1   yl, yr - 1
		vec[xl].pb(mp(i, mp(yl, yr - 1)));
		vec[xr].pb(mp(-i, mp(yl, yr - 1)));
		x[i] = xl;
	}
	rep(i, 1, q + 1) {
		int x, y; cin >> x >> y;
		// x, x + l - 1   y, y + w - 1
		vec[x - 1].pb(mp(-(i + n), mp(y, y + w - 1)));
		vec[x + l - 1].pb(mp((i + n), mp(y, y + w - 1)));
	}
	// build
	rep(i, 0, 1e6 + 1) {
		for(auto u : vec[i]) {
			int id = abs(u.fi); if(id > n) id -= n;
			int l = u.se.fi, r = u.se.se;
			if(u.fi > 0) {
				if(u.fi <= n) {
					seg[0].upd(l, r, 1);
					seg[1].upd(l, r, i);
				} else {
					ll a[3];
					rep(i, 0, 3) a[i] = seg[i].qry(l, r);
					ll res = a[2] - a[1] + a[0] * (i + 1);
					ans[id] += res;
				}
			} else {
				if(-u.fi <= n) {
					seg[0].upd(l, r, -1);
					seg[1].upd(l, r, -x[id]);
					seg[2].upd(l, r, i - x[id]);
				} else {
					ll a[3];
					rep(i, 0, 3) a[i] = seg[i].qry(l, r);
					ll res = a[2] - a[1] + a[0] * (i + 1);
					ans[id] -= res;
				}
			}
		}
	}
	rep(i, 1, q + 1) cout << ans[i] << endl;
	return 0;
}
