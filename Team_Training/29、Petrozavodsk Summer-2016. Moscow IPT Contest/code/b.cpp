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

const int N = 505050;

int n, a[N];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int la[N], a[N], o[N], mi[N];
	void up(int rt) {
		a[rt] = a[ls] & a[rs];
		o[rt] = o[ls] | o[rs];
		mi[rt] = min(mi[ls], mi[rs]);
	}
	void build(int l = 1, int r = n, int rt = 1) {
		la[rt] = 0;
		if(l == r) {
			a[rt] = o[rt] = mi[rt] = ::a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	void gao(int rt, int c) {
		mi[rt] += c;
		a[rt] += c;
		o[rt] += c;
		la[rt] += c;
	}
	void down(int rt) {
		if(la[rt]) {
			gao(ls, la[rt]);
			gao(rs, la[rt]);
			la[rt] = 0;
		}
	}
	void updand(int L, int R, int c, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R && ((a[rt] & ~c) == (o[rt] & ~c))) {
			int x = (a[rt] & ~c);
			gao(rt, -x);
			return ;
		}
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) updand(L, R, c, l, mid, ls);
		if(R > mid) updand(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	void updor(int L, int R, int c, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R && ((a[rt] & c) == (o[rt] & c))) {
			int x = (~a[rt] & c);
			gao(rt, x);
			return ;
		}
		int mid = l + r >> 1;
		down(rt);
		if(L <= mid) updor(L, R, c, l, mid, ls);
		if(R > mid) updor(L, R, c, mid + 1, r, rs);
		up(rt);
	}
	int qry(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return mi[rt];
		int mid = l + r >> 1, ans = pw(30);
		down(rt);
		if(L <= mid) ans = min(ans, qry(L, R, l, mid, ls));
		if(R > mid) ans = min(ans, qry(L, R, mid + 1, r, rs));
		return ans;
	}
}seg;

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	cin >> n;
	rep(i, 1, n + 1) cin >> a[i];
	int m; cin >> m;
	seg.build();
	rep(i, 1, m + 1) {
		string o; int l, r, x;
		cin >> o >> l >> r;
		if(o[0] == '&') {
			cin >> x;
			seg.updand(l, r, x);
		} else if(o[0] == '|') {
			cin >> x;
			seg.updor(l, r, x);
		} else {
			cout << seg.qry(l, r) << endl;
		}
	}
	return 0;
}
