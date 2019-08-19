#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl '\n'
#define sz(x) (int)x.size()
#define all(x) x.begin(), x.end()
#define pw(x) (1ll<<(x))
typedef long long ll;
typedef double db;
typedef vector<int> vi;
typedef pair<int, int> pii;

const int N = 202020;

int n, m, a[N], x[N << 2], my[N << 2], len;
vi V;

int F(int x) {
	return lower_bound(all(V), x) - V.begin() + 1;
}

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 1 << 1 << 2, inf = 1e9 + 7;
	int lef[N], rig[N];
	pair<pii, int> nd[N];
	void up(int rt) {
		if(~rig[rs]) rig[rt] = rig[rs];
		else rig[rt] = rig[ls];
		if(~lef[ls]) lef[rt] = lef[ls];
		else lef[rt] = lef[rs];
		nd[rt] = mp(pii(0, 0), inf);
		if(nd[ls].se < nd[rt].se) nd[rt] = nd[ls];
		if(nd[rs].se < nd[rt].se) nd[rt] = nd[rs];
		if((~rig[ls]) && (~lef[rs])) {
			int x = rig[ls], y = lef[rs];
			if(y > sz(V)) y -= sz(V);
			x = V[x - 1], y = V[y - 1];
			x = (m - x) % m;
			int t = (x + y) % m;
			if(t < nd[rt].se) nd[rt] = mp(mp(x, y), t);
		}
	}
	void build(int l = 1, int r = len, int rt = 1) {
		if(l == r) {
			lef[rt] = rig[rt] = -1;
			if(my[l]) rig[rt] = l;
			if(x[l]) lef[rt] = l;
			nd[rt] = mp(pii(0, 0), inf);
			if(my[l] && x[l]) {
				int t = V[l - 1];
				t = (m - t) % m;
				nd[rt] = mp(pii(t, V[l - 1]), 0);
			}
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void upd(int p, int l = 1, int r = len, int rt = 1) {
		if(l == r) {
			lef[rt] = rig[rt] = -1;
			if(my[l]) rig[rt] = l;
			if(x[l]) lef[rt] = l;
			nd[rt] = mp(pii(0, 0), inf);
			if(my[l] && x[l]) {
				int t = V[l - 1];
				t = (m - t) % m;
				nd[rt] = mp(pii(t, V[l - 1]), 0);
			}
			return ;
		}
		int mid = l + r >> 1;
		if(p <= mid) upd(p, l, mid, ls);
		else upd(p, mid + 1, r, rs);
		up(rt);
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n >> m;
	rep(i, 1, n + 1) cin >> a[i], V.pb(a[i]), V.pb((m - a[i]) % m);
	sort(all(V));
	V.erase(unique(all(V)), V.end());
	len = sz(V) * 2;
	int t = F(a[1]);
	++x[t], ++x[t + sz(V)];
	rep(i, 2, n + 1) {
		int t = F((m - a[i]) % m);
		++my[t];
	}
	seg.build();
	ll ans = 0;
	rep(i, 2, n + 1) {
		auto &u = seg.nd[1];
		ans += u.se;
		int x = u.fi.fi, y = u.fi.se;
		int t = F((m - x) % m);
		--my[t];
		seg.upd(t);
		t = F(x);
		++::x[t];
		++::x[t + sz(V)];
		seg.upd(t);
		seg.upd(t + sz(V));
	}
	cout << ans << endl;
	return 0;
}
