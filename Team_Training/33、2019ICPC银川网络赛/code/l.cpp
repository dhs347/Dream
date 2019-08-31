#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define mp make_pair
#define pb push_back
#define rep(i, a, b) for(int i=(a); i<(b); i++)
#define per(i, a, b) for(int i=(b)-1; i>=(a); i--)
#define sz(a) (int)a.size()
#define de(a) cout << #a << " = " << a << endl
#define dd(a) cout << #a << " = " << a << " "
#define all(a) a.begin(), a.end()
#define pw(x) (1ll<<(x))
#define endl "\n"
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
typedef double db;

const int N = 101010;

int n, a[N];
vi ma, mi;

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int cnt[N];
	ll mi[N], la[N];
	void gao(int rt, int c) {
		mi[rt] += c; la[rt] += c;
	}
	void down(int rt) {
		if(la[rt]) {
			gao(ls, la[rt]);
			gao(rs, la[rt]);
			la[rt] = 0;
		}
	}
	void up(int rt) {
		mi[rt] = min(mi[ls], mi[rs]);
		cnt[rt] = 0;
		if(mi[rt] == mi[ls]) cnt[rt] += cnt[ls];
		if(mi[rt] == mi[rs]) cnt[rt] += cnt[rs];
	}
	void build(int l, int r, int rt) {
		mi[rt] = 1; la[rt] = 0; cnt[rt] = r - l + 1;
		if(l == r) return ;
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
	}
	void upd(int L, int R, ll c, int l, int r, int rt) {
	//	if(rt == 1) dd(L), dd(R), de(c);
		if(L <= l && r <= R) {
			gao(rt, c);
			return ;
		}
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) upd(L, R, c, l, mid, ls);
		if(R > mid) upd(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	int qry(int L, int R, int l, int r, int rt) {
		if(L <= l && r <= R) return cnt[rt] * (mi[rt] == 0);
		int mid = l + r >> 1, ans = 0;
		down(rt);
		if(L <= mid) ans += qry(L, R, l, mid, ls);
		if(R > mid) ans += qry(L, R, mid + 1, r, rs);
		return ans;
	}
}seg;

void solve() {
	cin >> n;
	ma.clear(), mi.clear();
	ma.pb(0), mi.pb(0);
	map<int, int> pre;
	ll ans = 0;
	seg.build(1, n, 1);
	rep(i, 1, n + 1) {
		int x; cin >> x; a[i] = x;
		seg.upd(pre[x] + 1, i, -1, 1, n, 1); pre[x] = i;
		while(sz(ma) > 1 && a[ma.back()] < x) {
			seg.upd(ma[sz(ma) - 2] + 1, ma.back(), x - a[ma.back()], 1, n, 1);
			ma.pop_back();
		}
		seg.upd(i, i, x, 1, n, 1); ma.pb(i);
		while(sz(mi) > 1 && a[mi.back()] > x) {
			seg.upd(mi[sz(mi) - 2] + 1, mi.back(), a[mi.back()] - x, 1, n, 1);
			mi.pop_back();
		}
		seg.upd(i, i, -x, 1, n, 1); mi.pb(i);
		ans += seg.qry(1, i, 1, n, 1);
	//	cout << endl;
	}
	cout << ans << endl;
}

int main() {
	std::ios::sync_with_stdio(false);
	std::cin.tie(0);
	int T; cin >> T;
	rep(i, 1, T + 1) {
		cout << "Case #" << i << ": ";
		solve();
	}
	return 0;
}

