#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define pb push_back
#define mp make_pair
#define per(i, a, b) for(int i = (b) - 1; i >= (a); --i)
#define rep(i, a, b) for(int i = (a); i < (b); ++i)
#define de(x) cout << #x << " = " << x << endl
#define dd(x) cout << #x << " = " << x << " "
#define endl "\n"
#define pw(x) (1ll<<(x))
#define all(x) x.begin(), x.end()
#define sz(x) (int)x.size()
typedef long long ll;
typedef pair<int, int> pii;
typedef double db;
typedef vector<int> vi;

const int N = 101010;

int n, m, a[N], root[N];

struct Seg {
	static const int N = 1e7;
	int ls[N], rs[N], cnt[N], cntn;
	void init() {
		cntn = 0;
	}
	inline void upd(int pre, int &now, int p, int l, int r) {
		now = ++cntn;
		ls[now] = ls[pre];
		rs[now] = rs[pre];
		cnt[now] = cnt[pre] + 1;
		if(l == r) return ;
		int mid = l + r >> 1;
		if(p <= mid) upd(ls[pre], ls[now], p, l, mid);
		else upd(rs[pre], rs[now], p, mid + 1, r);
	}
	inline int qry(int rt, int L, int R, int l, int r) {
		if(!rt) return 0;
		if(L <= l && r <= R) return cnt[rt];
		int mid = l + r >> 1, ans = 0;
		if(L <= mid) ans += qry(ls[rt], L, R, l, mid);
		if(R > mid) ans += qry(rs[rt], L, R, mid + 1, r);
		return ans;
	}
}seg;

inline int calc(int st, int ed, int l, int r) {
	l = max(1, l);
	r = min(r, 1000000);
	return seg.qry(root[ed], l, r, 1, 1e6) - seg.qry(root[st - 1], l, r, 1, 1e6);
}

void solve() {
	srand(time(0));
	cin >> n >> m;
	rep(i, 1, n + 1) a[i] = rand() % (1000000) + 1; //cin >> a[i];
	seg.init();
	rep(i, 1, n + 1) seg.upd(root[i - 1], root[i], a[i], 1, 1e6);
	while(m--) {
		int l, r, p, x;
		l = rand() % n + 1, r = rand() % n + 1;
		if(l > r) swap(l, r);
		p = rand() % (1000000) + 1, x = rand() % (r - l + 1) + 1;
	//	cin >> l >> r >> p >> x;
		int st = 0, ed = 1e6, ans = 0;
		while(st <= ed) {
			int mid = st + ed >> 1;
			if(calc(l, r, p - mid, p + mid) >= x) {
				ans = mid;
				ed = mid - 1;
			} else {
				st = mid + 1;
			}
		}
//		cout << ans << endl;
	}
}

int main() {
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int T; cin >> T;
	while(T--) solve();
	return 0;
}
