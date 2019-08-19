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

const int N = 5e5 + 7, M = 30;

int n, a[N], ans[M];

struct Seg {
#define ls rt << 1
#define rs ls | 1
	static const int N = ::N << 2;
	int la[M][N], mi[M][N];
	void up(int rt) {
		rep(i, 0, M) {
			int a = mi[i][ls] & (pw(i + 1) - 1);
			int b = mi[i][rs] & (pw(i + 1) - 1);
			mi[i][rt] = (a < b) ? mi[i][ls] : mi[i][rs];
		}
	}
	void build(int l = 1, int r = n, int rt = 1) {
		rep(i, 0, M) la[i][rt] = -1;
		if(l == r) {
			rep(i, 0, M) mi[i][rt] = a[l];
			return ;
		}
		int mid = l + r >> 1;
		build(l, mid, ls);
		build(mid + 1, r, rs);
		up(rt);
	}
	// 0: and
	void gao(int rt, int l, int r, int i, int o) {
		la[i][rt] = o;
		if(o == 0) mi[rt] &= (pw(M) - 1 - pw(i));
		else mi[rt] |= pw(i);
	}
	void down(int rt, int l, int r, int mid) {
		rep(i, 0, M) if(~la[i][rt]) {
			gao(ls, l, mid, i, la[i][rt]);
			gao(rs, mid + 1, r, i, la[i][rt]);
			la[i][rt] = -1;
		}
	}
	void upd(int L, int R, int c, int o, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) {
			rep(i, 0, M) if((c >> i & 1) == o) gao(rt, l, r, i, o);
			return ;
		}
		int mid = l + r >> 1;
		down(rt, l, r, mid);
		if(L <= mid) upd(L, R, c, o, l, mid, ls);
		if(R > mid) upd(L, R, c, o, mid + 1, r, rs);
		up(rt);
	}
	int qry(int L, int R, int l = 1, int r = n, int rt = 1) {
		if(L <= l && r <= R) return mi[rt];
		int mid = l + r >> 1, ans = pw(30);
		down(rt, l, r, mid);
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
	seg.build();
	int m; cin >> m;
	while(m--) {
		string s; int l, r, x; cin >> s >> l >> r;
		if(s[0] != '?') {
			cin >> x;
			seg.upd(l, r, x, s[0] == '|');
		} else {
			cout << seg.qry(l, r) << endl;
		}
	}
	return 0;
}
